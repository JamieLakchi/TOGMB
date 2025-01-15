#ifndef INC_RATS_VARIABLEPATTERN
#define INC_RATS_VARIABLEPATTERN

#include "declarations.h"
#include "ratterns/pattern.h"

namespace rats {

struct VariablePattern : public Pattern {
  PATTERN
  VariablePattern(const patternId varId);

  patternId _varId;
};

} // namespace rats

#endif
