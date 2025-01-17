#ifndef INC_CALCULATOR_CALCULATOR
#define INC_CALCULATOR_CALCULATOR

#include "ASTConverter.h"
#include "MathParser.h"
#include "../declarations.h"

namespace calculator {

class Calculator {
public:
  Calculator();

  void enterOperation(const string &input);

private:
  // parsing
  unique_ptr<MathParser> _parser;
  unique_ptr<ASTConverter> _toAST;

  // variables memory
  using scope = hashmap<string, Number>;
  struct LocalVarStackElem {
    scope _lvars;                        // local scope
    shared_ptr<LocalVarStackElem> _prev; // previous scope
  };

  shared_ptr<LocalVarStackElem> _lvars = nullptr;
  scope _gvars; // global scope

  // function memory
  using fscope = hashmap<string, shared_ptr<ASTNode>>;
  fscope _funcs; // function memory

  // parameters
  vector<Number> _args;
};

} // namespace calculator

#endif
