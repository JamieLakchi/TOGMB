#ifndef INC_RATS_PARSETREENODE
#define INC_RATS_PARSETREENODE

#include "declarations.h"

namespace rats {

struct ParseTreeNode {
  ParseTreeNode() = default;
  ParseTreeNode(const string &value);

  bool isTerminal() const;
  bool isTransition() const;
  string yield() const;
  void print() const;

  string _value;
  vector<shared_ptr<ParseTreeNode>> _children;
};

} // namespace rats

#endif
