#ifndef INC_RATS_VARNAMEPATTERN
#define INC_RATS_VARNAMEPATTERN

#include "declarations.h"
#include "pattern.h"

namespace rats {

struct VarNamePattern : public Pattern {
  PATTERN
  VarNamePattern() = default;
};

} // namespace rats

#endif
