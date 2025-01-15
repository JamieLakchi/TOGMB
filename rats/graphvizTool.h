#ifndef INC_RATS_GRAPHVIZTOOL
#define INC_RATS_GRAPHVIZTOOL

#include "declarations.h"
#include <cstddef>
#include <fstream>

namespace rats {

class GraphvizTool {
public:
  void createDotFile(const string &filename,
                     const shared_ptr<ParseTreeNode> &root);

private:
  string traverse(const shared_ptr<ParseTreeNode> &root);

  string newNode();
  string variableLabel(const string &text);
  string terminalLabel(const string &text);

  std::ofstream out;
  size_t nodecount = 0;
};

}; // namespace rats

#endif
