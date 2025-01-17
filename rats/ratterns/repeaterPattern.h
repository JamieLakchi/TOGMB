#ifndef INC_RATS_REPEATERPATTERN
#define INC_RATS_REPEATERPATTERN

#include "../../declarations.h"
#include "pattern.h"

namespace rats {

namespace Reps {
const size_t INF = 0;
}

struct RepeaterPattern : public Pattern {
  PATTERN
  RepeaterPattern(const size_t min, const size_t max,
                  shared_ptr<Pattern> pattern);

  size_t _min;
  size_t _max;
  shared_ptr<Pattern> _pattern;
};

} // namespace rats

#endif
