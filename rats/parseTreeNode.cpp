#include "parseTreeNode.h"
#include <iostream>

namespace rats {

ParseTreeNode::ParseTreeNode(const string &value) : _value{value} {}

bool ParseTreeNode::isTerminal() const { return _children.empty(); }

bool ParseTreeNode::isTransition() const { return _children.size() == 1; }

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

string ParseTreeNode::yield() const {
  if (isTerminal()) {
    return _value;
  }

  string ans;

  for (auto &child : _children) {
    auto res = child->yield();
    ans.insert(ans.end(), res.begin(), res.end());
  }

  return ans;
}

} // namespace rats
