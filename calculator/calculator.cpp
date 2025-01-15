#include "calculator.h"
#include "MathParser.h"
#include "declarations.h"

namespace calculator {

Calculator::Calculator()
    : _toAST{create_unique<ASTConverter>()},
      _parser{create_unique<MathParser>()} {}

void Calculator::enterOperation(const string &input) {
  static const set<char> whiteSpace{'\n', '\t', ' '};
  string cleanInput;

  for (char c : input) {
    auto found = whiteSpace.find(c);
    if (found == whiteSpace.end()) {
      cleanInput.push_back(c);
    }
  }

  auto parseresult = _parser->parse(cleanInput);

  if (!parseresult._success) {
    if (parseresult._ans) {
    } else {
    }
    return;
  }

  auto ast = _toAST->convert(parseresult._ans);
}

} // namespace calculator
