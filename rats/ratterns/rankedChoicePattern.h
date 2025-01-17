#ifndef INC_RATS_RANKEDCHOICEPATTERN
#define INC_RATS_RANKEDCHOICEPATTERN

#include "../../declarations.h"
#include "pattern.h"

namespace rats {

struct RankedChoicePattern : public Pattern {
  PATTERN
  template <typename... ARGS>
  RankedChoicePattern(ARGS &&...args) : _patterns{args...} {}

  vector<shared_ptr<Pattern>> _patterns;
};

} // namespace rats

#endif
