#ifndef INC_CALCULATOR_CALCULATOR
#define INC_CALCULATOR_CALCULATOR

#include "ASTConverter.h"
#include "MathParser.h"
#include "declarations.h"

namespace calculator {

class Calculator {
public:
  Calculator();

  void enterOperation(const string &input);

private:
  unique_ptr<MathParser> _parser;
  unique_ptr<ASTConverter> _toAST;
};

} // namespace calculator

#endif
