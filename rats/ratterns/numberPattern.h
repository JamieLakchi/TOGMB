#ifndef INC_RATS_NUMBERPATTERN
#define INC_RATS_NUMBERPATTERN

#include "../../declarations.h"
#include "pattern.h"

namespace rats {

struct NumberPattern : public Pattern {
  PATTERN
  NumberPattern() = default;
};

} // namespace rats

#endif
