#ifndef INC_CALCULATOR_ASTCONVERTER
#define INC_CALCULATOR_ASTCONVERTER

#include "declarations.h"
#include "parseTreeNode.h"
namespace calculator {

struct ASTNode {
  enum class Type {
    FunctionAssign,
    VariableAssign,
    Evaluation,
    Operation,
    Number,
    Variable,
  };

  ASTNode(Type t);
  ~ASTNode();

  Type type;

  struct FunctionAssignInfo {
    string name;
    vector<string> variables; // names for local scope
    shared_ptr<ASTNode> operation;
  };

  struct VariableAssignInfo {
    string name;
    shared_ptr<ASTNode>
        expression; // should be evaluated to number upon assigning
  };

  struct EvaluationInfo {
    shared_ptr<ASTNode> expression;
  };

  struct OperationInfo {
    string signature;
    vector<shared_ptr<ASTNode>>
        variables; // to be evaluated and passed as params
  };

  struct NumberInfo {
    Number value;
  };

  struct VariableInfo {
    string name;
  };

  union {
    FunctionAssignInfo functionAssign;
    VariableAssignInfo variableAssign;
    EvaluationInfo evaluation;
    OperationInfo operation;
    NumberInfo number;
    VariableInfo variable;
  };
};

class ASTConverter {
public:
  shared_ptr<ASTNode> convert(shared_ptr<rats::ParseTreeNode> &root);

private:
  using c_functype =
      shared_ptr<ASTNode> (ASTConverter::*)(shared_ptr<rats::ParseTreeNode> &);

  shared_ptr<ASTNode> _convert(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_evaluate(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_assignfunc(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_assignvar(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_superexpr(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_expr(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_term(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_factor(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_number(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_function(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_variable(shared_ptr<rats::ParseTreeNode> &root);
};

} // namespace calculator

#endif
