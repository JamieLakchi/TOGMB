#ifndef INC_RATS_GRAPHVIZTOOL
#define INC_RATS_GRAPHVIZTOOL

#include "calculator/ASTConverter.h"
#include "declarations.h"
#include <cstddef>
#include <fstream>

class GraphvizTool {
public:
  template <typename TREE_T>
  void createDotFile(const string &filename, const TREE_T &root) {
    out = std::ofstream{filename};

    if (!out.is_open())
      return;

    out << "digraph m{" << std::endl;

    auto rootname = traverse(root);

    out << "}";

    out.close();
  }

private:
  string traverse(const shared_ptr<rats::ParseTreeNode> &root);
  string traverse(const shared_ptr<calculator::ASTNode> &root);

  string newNode();
  string variableLabel(const string &text);
  string terminalLabel(const string &text);
  string boxLabel(const string &text);

  std::ofstream out;
  size_t nodecount = 0;
};

#endif
