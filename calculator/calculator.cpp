#include "calculator.h"
#include "ASTConverter.h"
#include "MathParser.h"
#include "declarations.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <utility>

namespace calculator {

CalculatorMemory::LocalVarStackElem::LocalVarStackElem(
    shared_ptr<LocalVarStackElem> prev)
    : _prev{std::move(prev)} {}

CalculatorMemory::FunctionScopeEntry::FunctionScopeEntry(
    CalcFunction func, size_t varCount, const string &definition)
    : _func{func}, _varCount{varCount}, _definition{definition} {}

Number *CalculatorMemory::findVar(const string &name) {
  if (_lvars) {
    auto found = _lvars->_lvars.find(name);
    if (found != _lvars->_lvars.end()) {
      return &found->second;
    }
  }

  auto found = _gvars.find(name);
  if (found != _gvars.end()) {
    return &found->second;
  }

  return nullptr;
}

Calculator::OperationResult::OperationResult(Type type, const string &message)
    : _type{type}, _message{message} {}

Calculator::Calculator()
    : _toAST{create_unique<ASTConverter>()},
      _parser{create_unique<MathParser>()},
      _mem{create_unique<CalculatorMemory>()} {
  CalculatorMemory::FunctionScopeEntry a;
  _mem->_funcs = {
      {"+",
       {[](CalculatorMemory &m) { return m._args[0] + m._args[1]; }, 2,
        "adds two numbers"}},
      {"-",
       {[](CalculatorMemory &m) { return m._args[0] - m._args[1]; }, 2,
        "subtracts two numbers"}},
      {"*",
       {[](CalculatorMemory &m) { return m._args[0] * m._args[1]; }, 2,
        "multiplies two numbers"}},
      {"/",
       {[](CalculatorMemory &m) { return m._args[0] / m._args[1]; }, 2,
        "divides two numbers"}},
      {"Neg",
       {[](CalculatorMemory &m) { return -m._args[0]; }, 1,
        "negates a number"}},
      {"pow",
       {[](CalculatorMemory &m) { return std::pow(m._args[0], m._args[1]); }, 2,
        "raises first number to the second number"}},
      {"sin",
       {[](CalculatorMemory &m) { return std::sin(m._args[0]); }, 1,
        "takes the sin of a number (rad)"}},
      {"cos",
       {[](CalculatorMemory &m) { return std::cos(m._args[0]); }, 1,
        "takes the cos of a number (rad)"}},
      {"log",
       {[](CalculatorMemory &m) {
          return std::log(m._args[1]) / std::log(m._args[0]);
        },
        2,
        "takes the logarithm of the second number base first "
        "number"}}};                         // initial functions
  _mem->_gvars = {{"pi", M_PI}, {"e", M_E}}; // initial vars
}

shared_ptr<Calculator::OperationResult>
Calculator::enterOperation(const string &input) {
  static const set<char> whiteSpace{'\n', '\t', ' '};
  string cleanInput;

  for (char c : input) {
    auto found = whiteSpace.find(c);
    if (found == whiteSpace.end()) {
      cleanInput.push_back(c);
    }
  }

  auto parseresult = _parser->parse(cleanInput);

  if (!parseresult._success) {
    auto FailedPatterns = [&]() {
      string combined;
      for (auto &elem : parseresult._lastFailName) {
        combined += elem + "/";
      }
      combined.pop_back();
      return combined;
    };
    auto ret =
        cOR(OperationResult::Type::ParseError,
            "Unable to recognise " + FailedPatterns() + " at " +
                std::to_string(parseresult._lastPatternStart + 1) + ": " +
                cleanInput.substr(parseresult._lastPatternStart,
                                  cleanInput.size() -
                                      parseresult._lastPatternStart));
    ret->_parseTree = parseresult._ans;
    return ret;
  }

  auto ast = _toAST->convert(parseresult._ans);

  auto isInvalid = validate(ast);

  if (isInvalid) {
    isInvalid->_parseTree = parseresult._ans;
    isInvalid->_ast = ast;
    return isInvalid;
  }

  switch (ast->type) {
  case ASTNode::Type::Evaluation: {
    auto ans = _eval->evaluate(*_mem, ast->evaluation.expression);
    auto ret = cOR(OperationResult::Type::Evaluation, std::to_string(ans));
    ret->_parseTree = parseresult._ans;
    ret->_ast = ast;
    return ret;
  } break;
  case ASTNode::Type::VariableAssign: {
    auto &info = ast->variableAssign;
    auto ans = _eval->evaluate(*_mem, info.expression);
    _mem->_gvars[info.name] = ans;
    return cOR(OperationResult::Type::VariableAssign, std::to_string(ans));
  } break;
  case ASTNode::Type::FunctionAssign: {
    auto &info = ast->functionAssign;
    _mem->_funcs[info.name] = {[=](CalculatorMemory &m) {
                                 // load args into memory under correct names
                                 auto ls = cLS(m._lvars);

                                 for (size_t i = 0; i < info.variables.size();
                                      ++i) {
                                   ls->_lvars[info.variables[i]] = m._args[i];
                                 }

                                 m._lvars = ls;
                                 // do evaluation
                                 auto ans = _eval->evaluate(m, info.operation);
                                 // pop vars off local stack
                                 m._lvars = m._lvars->_prev;
                                 // return ans
                                 return ans;
                               },
                               info.variables.size(), cleanInput};
    auto ret = cOR(OperationResult::Type::FunctionAssign, "");
    ret->_parseTree = parseresult._ans;
    ret->_ast = ast;
    return ret;
  } break;
  default:
    break;
  };
  auto ret = cOR(OperationResult::Type::InvalidExpression,
                 "Unkown InvalidExpression error");
  ret->_parseTree = parseresult._ans;
  ret->_ast = ast;
  return ret;
}

shared_ptr<Calculator::OperationResult>
Calculator::cOR(Calculator::OperationResult::Type type, const string &message) {
  return create_shared<Calculator::OperationResult>(type, message);
}

shared_ptr<CalculatorMemory::LocalVarStackElem>
Calculator::cLS(shared_ptr<CalculatorMemory::LocalVarStackElem> &next) {
  return create_shared<CalculatorMemory::LocalVarStackElem>(next);
}

shared_ptr<Calculator::OperationResult>
Calculator::validate(shared_ptr<ASTNode> &root) {
  switch (root->type) {
  case ASTNode::Type::FunctionAssign: {
    return v_FunctionAssign(root);
  } break;
  case ASTNode::Type::VariableAssign: {
    return v_VariableAssign(root);
  } break;
  case ASTNode::Type::Evaluation: {
    return v_Evaluation(root);
  } break;
  case ASTNode::Type::Operation: {
    return v_Operation(root);
  } break;
  case ASTNode::Type::Number: {
    return v_Number(root);
  } break;
  case ASTNode::Type::Variable: {
    return v_Variable(root);
  } break;
  }
  return nullptr;
}

shared_ptr<Calculator::OperationResult>
Calculator::v_FunctionAssign(shared_ptr<ASTNode> &root) {
  auto &info = root->functionAssign;
  auto found = _mem->_funcs.find(info.name);

  if (found != _mem->_funcs.end()) {
    return cOR(OperationResult::Type::InvalidExpression,
               "Function with name \"" + info.name + "\" already exists!");
  }

  // temporary local stack
  auto temp_lscope = cLS(_mem->_lvars);
  _mem->_lvars = temp_lscope;

  for (auto &elem : info.variables) {
    temp_lscope->_lvars[elem] = 0;
  }

  auto ans = validate(info.operation);

  _mem->_lvars = _mem->_lvars->_prev; // pop temporary off stack

  return ans;
}

shared_ptr<Calculator::OperationResult>
Calculator::v_VariableAssign(shared_ptr<ASTNode> &root) {
  auto &info = root->variableAssign;
  auto found = _mem->findVar(info.name);

  if (found) {
    return cOR(OperationResult::Type::InvalidExpression,
               "Variable with name \"" + info.name + "\" already exists!");
  }

  auto ans = validate(info.expression);

  return ans;
}

shared_ptr<Calculator::OperationResult>
Calculator::v_Evaluation(shared_ptr<ASTNode> &root) {
  auto &info = root->evaluation;
  return validate(info.expression);
}

shared_ptr<Calculator::OperationResult>
Calculator::v_Operation(shared_ptr<ASTNode> &root) {
  auto &info = root->operation;
  auto found = _mem->_funcs.find(info.signature);
  if (found == _mem->_funcs.end()) {
    return cOR(OperationResult::Type::InvalidExpression,
               "Function with name \"" + info.signature + "\" doesn't exist!");
  }

  auto &funcInfo = found->second;
  if (funcInfo._varCount != info.variables.size()) {
    return cOR(OperationResult::Type::InvalidExpression,
               "Function \"" + info.signature + "\" requires " +
                   std::to_string(funcInfo._varCount) + " variables, given " +
                   std::to_string(info.variables.size()) + "!");
  }

  for (auto &var : info.variables) {
    auto ans = validate(var);
    if (ans) {
      return ans;
    }
  }

  return nullptr;
}

shared_ptr<Calculator::OperationResult>
Calculator::v_Number(shared_ptr<ASTNode> &root) {
  return nullptr;
}

shared_ptr<Calculator::OperationResult>
Calculator::v_Variable(shared_ptr<ASTNode> &root) {
  auto &info = root->variable;

  auto ans = _mem->findVar(info.name);

  if (!ans) {
    return cOR(OperationResult::Type::InvalidExpression,
               "Variable with name \"" + info.name + "\" doesn't exist!");
  }

  return nullptr;
}

} // namespace calculator
