#ifndef INC_CALCULATOR_ASTCONVERTER
#define INC_CALCULATOR_ASTCONVERTER

#include "../declarations.h"
#include "../rats/parseTreeNode.h"
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

  struct fa {
    string name;
    vector<string> variables; // names for local scope
    shared_ptr<ASTNode> operation;
  };

  struct vaa {
    string name;
    shared_ptr<ASTNode>
        expression; // should be evaluated to number upon assigning
  };

  struct ev {
    shared_ptr<ASTNode> expression;
  };

  struct op {
    string signature;
    vector<shared_ptr<ASTNode>>
        variables; // to be evaluated and passed as params
  };

  struct nu {
    Number value;
  };

  struct va {
    string name;
  };

  union {
    fa functionAssign;
    vaa variableAssign;
    ev evaluation;
    op operation;
    nu number;
    va variable;
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

  shared_ptr<ASTNode> c_expr(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_term(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_factor(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_number(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_function(shared_ptr<rats::ParseTreeNode> &root);

  shared_ptr<ASTNode> c_variable(shared_ptr<rats::ParseTreeNode> &root);
};

} // namespace calculator

#endif
