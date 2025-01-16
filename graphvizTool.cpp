#include "graphvizTool.h"
#include "calculator/ASTConverter.h"
#include "parseTreeNode.h"
#include <string>

string GraphvizTool::traverse(const shared_ptr<rats::ParseTreeNode> &root) {
  auto myName = newNode();
  out << myName
      << (root->isTerminal() ? terminalLabel(root->_value)
                             : variableLabel(root->_value))
      << ";" << std::endl;

  for (auto &child : root->_children) {
    auto childName = traverse(child);
    out << myName << "->" << childName
        << (child->isTerminal() ? "[style=dashed]" : "") << ";" << std::endl;
  }

  return myName;
}

string GraphvizTool::traverse(const shared_ptr<calculator::ASTNode> &root) {
  using namespace calculator;
  auto myName = newNode();
  switch (root->type) {
  case ASTNode::Type::FunctionAssign: {
    auto &info = root->functionAssign;
    string templabel = "assign: " + info.name + "( ";
    for (auto &varname : info.variables) {
      templabel += varname + " ";
    }
    templabel += ")";
    auto myLabel = boxLabel(templabel);
    out << myName << myLabel << ";" << std::endl;
    auto expr = traverse(info.operation);
    out << myName << "->" << expr << ";" << std::endl;
  } break;
  case ASTNode::Type::VariableAssign: {
    auto &info = root->variableAssign;
    auto myLabel = boxLabel("assign: " + info.name);
    out << myName << myLabel << ";" << std::endl;
    auto expr = traverse(info.expression);
    out << myName << "->" << expr << ";" << std::endl;
  } break;
  case ASTNode::Type::Evaluation: {
    return traverse(root->evaluation.expression);
  } break;
  case ASTNode::Type::Operation: {
    auto &info = root->operation;
    auto myLabel = boxLabel("op: " + info.signature);
    out << myName << myLabel << ";" << std::endl;
    for (auto &param : info.variables) {
      auto expr = traverse(param);
      out << myName << "->" << expr << ";" << std::endl;
    }
  } break;
  case ASTNode::Type::Number: {
    auto &info = root->number;
    auto myLabel = terminalLabel(std::to_string(info.value));
    out << myName << myLabel << ";" << std::endl;
  } break;
  case ASTNode::Type::Variable: {
    auto &info = root->variable;
    auto myLabel = terminalLabel(info.name);
    out << myName << myLabel << ";" << std::endl;
  } break;
  }

  return myName;
}

string GraphvizTool::newNode() {
  return string{"node" + std::to_string(++nodecount)};
}

string GraphvizTool::variableLabel(const string &text) {
  return string{"[label=\"" + text + "\"]"};
}

string GraphvizTool::terminalLabel(const string &text) {
  return string{
      "[label=\"" + text +
      "\", style=dashed, fillcolor=lightgrey, style=\"filled,dashed\"]"};
}

string GraphvizTool::boxLabel(const string &text) {
  return string{"[label=\"" + text + "\", shape=box]"};
}
