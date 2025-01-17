#ifndef INC_RATS_SEQUENCEPATTERN
#define INC_RATS_SEQUENCEPATTERN

#include "../../declarations.h"
#include "pattern.h"

namespace rats {

struct SequencePattern : public Pattern {
  PATTERN
  template <typename... ARGS>
  SequencePattern(ARGS &&...args) : _patterns{args...} {}

  vector<shared_ptr<Pattern>> _patterns;
};

} // namespace rats

#endif
