#include "ASTConverter.h"
#include "declarations.h"
#include "grammarSymbols.h"
#include <string>

namespace calculator {

/*
 switch (type) {
  case ASTNode::Type::FunctionAssign: {
  } break;
  case ASTNode::Type::VariableAssign: {
  } break;
  case ASTNode::Type::Evaluation: {
  } break;
  case ASTNode::Type::Operation: {
  } break;
  case ASTNode::Type::Number: {
  } break;
  case ASTNode::Type::Variable: {
  } break;
  }
 */

#define ACTIVATE(_name) new (&_name) decltype(_name);
// this don't work for some reason#define DESTROY(_name)
// _name.~decltype(_name)()

ASTNode::ASTNode(Type t) : type{t} {
  // activate correct union type
  switch (type) {
  case ASTNode::Type::FunctionAssign: {
    ACTIVATE(functionAssign);
  } break;
  case ASTNode::Type::VariableAssign: {
    ACTIVATE(variableAssign);
  } break;
  case ASTNode::Type::Evaluation: {
    ACTIVATE(evaluation);
  } break;
  case ASTNode::Type::Operation: {
    ACTIVATE(operation);
  } break;
  case ASTNode::Type::Number: {
    ACTIVATE(number);
  } break;
  case ASTNode::Type::Variable: {
    ACTIVATE(variable);
  } break;
  }
}
ASTNode::~ASTNode() {
  switch (type) {
  case ASTNode::Type::FunctionAssign: {
    functionAssign.operation = nullptr;
    functionAssign.variables.clear();
    functionAssign.~FunctionAssignInfo();
  } break;
  case ASTNode::Type::VariableAssign: {
    variableAssign.expression = nullptr;
    variableAssign.~VariableAssignInfo();
  } break;
  case ASTNode::Type::Evaluation: {
    evaluation.expression = nullptr;
    evaluation.~EvaluationInfo();
  } break;
  case ASTNode::Type::Operation: {
    operation.variables.clear();
    operation.~OperationInfo();
  } break;
  case ASTNode::Type::Number: {
    number.~NumberInfo();
  } break;
  case ASTNode::Type::Variable: {
    variable.~VariableInfo();
  } break;
  }
}

shared_ptr<ASTNode>
ASTConverter::convert(shared_ptr<rats::ParseTreeNode> &root) {
  if (root->_value != sym::Statement || !root->isTransition()) {
    return nullptr;
  }

  return _convert(root->_children[0]);
}

shared_ptr<ASTNode>
ASTConverter::_convert(shared_ptr<rats::ParseTreeNode> &root) {
  static const hashmap<string, c_functype> converters{
      {sym::Evaluate, &ASTConverter::c_evaluate},
      {sym::AssignFunction, &ASTConverter::c_assignfunc},
      {sym::AssignVariable, &ASTConverter::c_assignvar},
      {sym::SuperExpr, &ASTConverter::c_superexpr},
      {sym::Expr, &ASTConverter::c_expr},
      {sym::Term, &ASTConverter::c_term},
      {sym::Factor, &ASTConverter::c_factor},
      {sym::Number, &ASTConverter::c_number},
      {sym::Function, &ASTConverter::c_function},
      {sym::Variable, &ASTConverter::c_variable}};

  auto rsym = root->_value;
  auto it = converters.find(rsym);

  if (it != converters.end()) {
    return (this->*(it->second))(root);
  }

  return nullptr;
}

shared_ptr<ASTNode>
ASTConverter::c_evaluate(shared_ptr<rats::ParseTreeNode> &root) {
  auto ans = create_shared<ASTNode>(ASTNode::Type::Evaluation);
  ans->evaluation.expression = c_superexpr(root->_children[0]);
  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_assignfunc(shared_ptr<rats::ParseTreeNode> &root) {
  // can only be name-"("-variablelist-")"-"="-expr
  auto ans = create_shared<ASTNode>(ASTNode::Type::FunctionAssign);
  ans->functionAssign.name = root->_children[0]->yield();

  // variable list traverse either varname-","-variablelist or varname
  auto current = root->_children[2];
  while (true) {
    if (current->isTransition()) {
      ans->functionAssign.variables.push_back(current->_children[0]->yield());
      break;
    } else {
      ans->functionAssign.variables.push_back(current->_children[0]->yield());
      current = current->_children[2]; // skip the ","
    }
  }

  ans->functionAssign.operation = c_superexpr(root->_children[5]);

  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_assignvar(shared_ptr<rats::ParseTreeNode> &root) {
  // can only be name-"="-expr
  auto ans = create_shared<ASTNode>(ASTNode::Type::VariableAssign);

  ans->variableAssign.name = root->_children[0]->yield();
  ans->variableAssign.expression = c_superexpr(root->_children[2]);

  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_superexpr(shared_ptr<rats::ParseTreeNode> &root) {
  // ("-/+")/("") - term - ("+/-" - expr)/("")
  //  1/0 - 1 - 2/0 => possible sizes = {
  //  1(just term),
  //  2(sign - term),
  //  3(term - op - expr ),
  //  4(sign - term - op - expression)
  //  }

  switch (root->_children.size()) {
  case 1: {
    return c_term(root->_children[0]);
  } break;
  case 2: {
    auto child = c_term(root->_children[1]);
    if (root->_children[0]->_value[0] == '-') {
      auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
      ans->operation.signature = "Neg";
      ans->operation.variables = {child};
      return ans;
    }
    return child;
  } break;
  case 3: {
    auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
    ans->operation.signature = root->_children[1]->_value;
    ans->operation.variables = {c_term(root->_children[0]),
                                c_expr(root->_children[2])};
    return ans;
  } break;
  case 4: {
    auto param1 = c_term(root->_children[1]);
    if (root->_children[0]->_value[0] == '-') {
      auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
      ans->operation.signature = "Neg";
      ans->operation.variables = {param1};
      param1 = ans;
    }
    auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
    ans->operation.signature = root->_children[2]->_value;
    ans->operation.variables = {param1, c_expr(root->_children[3])};
    return ans;
  } break;
  }

  throw "Not so clever";
}

shared_ptr<ASTNode>
ASTConverter::c_expr(shared_ptr<rats::ParseTreeNode> &root) {
  if (root->isTransition()) { // not recursive case
    return c_term(root->_children[0]);
  }

  // recursive case will be term-operator-expr
  auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
  ans->operation.signature = root->_children[1]->_value;
  ans->operation.variables = {c_term(root->_children[0]),
                              c_expr(root->_children[2])};
  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_term(shared_ptr<rats::ParseTreeNode> &root) {
  if (root->isTransition()) { // not recursive case
    return c_factor(root->_children[0]);
  }

  // recursive case will be factor-operator-expr
  auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);
  ans->operation.signature = root->_children[1]->_value;
  ans->operation.variables = {c_factor(root->_children[0]),
                              c_term(root->_children[2])};
  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_factor(shared_ptr<rats::ParseTreeNode> &root) {
  if (root->isTransition()) { // could be number, function, or variable
    return _convert(root->_children[0]);
  }

  // bracketed expression "("-superexpr-")"
  return c_superexpr(root->_children[1]);
}

shared_ptr<ASTNode>
ASTConverter::c_number(shared_ptr<rats::ParseTreeNode> &root) {
  // can only be number
  auto ans = create_shared<ASTNode>(ASTNode::Type::Number);
  ans->number.value = std::stold(root->yield());
  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_function(shared_ptr<rats::ParseTreeNode> &root) {
  // can only be function: name-"("-exprlist-")"
  auto ans = create_shared<ASTNode>(ASTNode::Type::Operation);

  ans->operation.signature = root->_children[0]->yield();

  // expression list traverse either superexpr-","-exprlist or superexpr
  auto current = root->_children[2];
  while (true) {
    if (current->isTransition()) {
      ans->operation.variables.push_back(c_superexpr(current->_children[0]));
      break;
    } else {
      ans->operation.variables.push_back(c_superexpr(current->_children[0]));
      current = current->_children[2]; // skip the ","
    }
  }

  return ans;
}

shared_ptr<ASTNode>
ASTConverter::c_variable(shared_ptr<rats::ParseTreeNode> &root) {
  // can only be variable
  auto ans = create_shared<ASTNode>(ASTNode::Type::Variable);
  ans->variable.name = root->yield();
  return ans;
}

} // namespace calculator
