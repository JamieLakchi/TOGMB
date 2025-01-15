#ifndef INC_CALCULATOR_ASTCONVERTER
#define INC_CALCULATOR_ASTCONVERTER

#include "declarations.h"
#include "parseTreeNode.h"
namespace calculator {

struct ASTNode {
  enum Type {
    AssignFunction,
  };
};

class ASTConverter {
public:
  shared_ptr<ASTNode> convert(shared_ptr<rats::ParseTreeNode> &root);

private:
  shared_ptr<ASTNode> _convert(shared_ptr<rats::ParseTreeNode> &root);
};

} // namespace calculator

#endif
