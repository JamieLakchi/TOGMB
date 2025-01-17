#ifndef INC_CALCULATOR_MATHPARSER
#define INC_CALCULATOR_MATHPARSER

#include "../declarations.h"
#include "../rats/rats.h"
#include <utility>

namespace calculator {

class MathParser {
public:
  MathParser();

  rats::Parser::ParseResult parse(const string &input);

private:
  unique_ptr<rats::Parser> _parser;
};

} // namespace calculator

#endif
