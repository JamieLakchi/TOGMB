#include "graphvizTool.h"
#include "parseTreeNode.h"

namespace rats {
void GraphvizTool::createDotFile(const string &filename,
                                 const shared_ptr<ParseTreeNode> &root) {
  out = std::ofstream{filename};

  if (!out.is_open())
    return;

  out << "digraph m{" << std::endl;

  auto rootname = traverse(root);

  out << "}";

  out.close();
}

string GraphvizTool::traverse(const shared_ptr<ParseTreeNode> &root) {

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

} // namespace rats

/*

string readFileToString(const std::string &filename) {
  std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

  auto fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  std::string content(static_cast<size_t>(fileSize), '\0');

  file.read(&content[0], fileSize);

  return content;
}

class toGraphviz {
public:
  toGraphviz(const string &filename) : m_filename(filename) {}

  void create(shared_ptr<PatternResult> root, const string &parsed) {
    out = std::ofstream{m_filename};

    if (!out.is_open())
      return;

    m_parsed = &parsed;

    rootstack.clear();
    rootstack.push_back(root);
    nodenamestack.clear();
    samerank.clear();

    counter = 0;
    namedNodeBelow = false;

    out << "digraph m{" << std::endl;

    create();

    if (!samerank.empty()) {
      out << "{ rank=same; ";
      for (auto &elem : samerank) {
        out << elem << ";";
      }
      out << "}" << std::endl;
    }

    out << "}";

    rootstack.clear();
    rootstack.push_back(root);
    nodenamestack.clear();
    samerank.clear();

    counter = 0;
    namedNodeBelow = false;
  }

private:
  string newNode() { return string{"node" + std::to_string(++counter)}; }
  string newLabel(const string &name, const bool result) {
    return string{"[label=\"" + name + " " + (result ? " ✓" : " ✗") + "\"]"};
  }
  string newTextField(const string &text) {
    return string{
        "[label=\"" + text +
        "\", style=dashed, fillcolor=lightgrey, style=\"filled,dashed\"]"};
  }

  void create() {
    if (rootstack.empty()) {
      namedNodeBelow = false;
      return;
    }

    // Get current node to process
    //  label += currentResult->m_success ? " ✓" : " ✗";
    auto currentResult = rootstack.back();
    rootstack.pop_back();

    bool isNamed = (bool)(currentResult->m_parsername);
    string nodename;

    if (isNamed) {
      nodename = newNode();
      auto nodelabel =
          newLabel(*currentResult->m_parsername, currentResult->m_success);

      out << nodename << nodelabel << ";" << std::endl;

      if (!nodenamestack.empty()) {
        auto &prev = nodenamestack.back();
        out << prev << " -> " << nodename << ";" << std::endl;
      }

      nodenamestack.push_back(nodename);
    }

    auto &newroots = currentResult->m_children;
    bool anyLowerNodesNamed = false;
    for (auto rbegin = newroots.begin(); rbegin != newroots.end(); ++rbegin) {
      auto &root = *rbegin;
      rootstack.push_back(root);
      create();
      anyLowerNodesNamed = anyLowerNodesNamed || namedNodeBelow;
    }

    if (!anyLowerNodesNamed && isNamed && m_parsed &&
        currentResult->m_length > 0 && !nodenamestack.empty()) {
      auto &lastnodename = nodenamestack.back();
      auto newtextnode = newNode();
      string matchedText =
          m_parsed->substr(currentResult->m_start, currentResult->m_length);

      size_t pos = 0;
      while ((pos = matchedText.find("\"", pos)) != string::npos) {
        matchedText.replace(pos, 1, "\\\"");
        pos += 2;
      }

      auto newtextfield = newTextField(matchedText);
      out << newtextnode << newtextfield << ";" << std::endl;
      out << lastnodename << " -> " << newtextnode << "[style=dashed];"
          << std::endl;

      samerank.push_back(newtextnode);
    }

    if (currentResult->m_parsername) {
      nodenamestack.pop_back();
    }

    namedNodeBelow = anyLowerNodesNamed || isNamed;
  }

  string m_filename;
  const string *m_parsed;
  std::ofstream out;
  vector<shared_ptr<PatternResult>> rootstack;
  vector<string> nodenamestack;
  vector<string> samerank;
  size_t counter = 0;
  bool namedNodeBelow = false;
};


 */
