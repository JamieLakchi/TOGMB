#ifndef INC_RATS_LITERALPATTERN
#define INC_RATS_LITERALPATTERN

#include "pattern.h"

namespace rats {

struct LiteralPattern : public Pattern {
  PATTERN;

  LiteralPattern(const string &literal);

  string _literal;
};

} // namespace rats

#endif
