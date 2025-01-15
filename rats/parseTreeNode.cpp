#include "parseTreeNode.h"
#include <iostream>

namespace rats {

ParseTreeNode::ParseTreeNode(const string &value) : _value{value} {}

bool ParseTreeNode::isTerminal() const { return _children.empty(); }

void ParseTreeNode::print() const {
  if (isTerminal()) {
    std::cout << _value;
    return;
  }
  std::cout << "{" << _value << ": ";
  for (auto &child : _children) {
    child->print();
  }
  std::cout << "}";
}

} // namespace rats
