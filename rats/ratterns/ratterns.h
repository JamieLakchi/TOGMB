#ifndef INC_RATS_RATTERNS
#define INC_RATS_RATTERNS

#include "declarations.h"
#include "literalPattern.h"
#include "namedPattern.h"
#include "numberPattern.h"
#include "pattern.h"
#include "rankedChoicePattern.h"
#include "repeaterPattern.h"
#include "sequencePattern.h"
#include "variablePattern.h"
#include <utility>

namespace rats {

shared_ptr<Pattern> term(const string &literal);

shared_ptr<Pattern> var(const patternId id);

template <typename... ARGS> shared_ptr<Pattern> seq(ARGS &&...args);

template <typename... ARGS> shared_ptr<Pattern> oneof(ARGS &&...args);

shared_ptr<Pattern> rep(const size_t min, const size_t max,
                        shared_ptr<Pattern> pattern);

shared_ptr<Pattern> num();

shared_ptr<Pattern> named(const string &name, shared_ptr<Pattern> pattern);

}; // namespace rats

// template definitions
namespace rats {

template <typename... ARGS> shared_ptr<Pattern> seq(ARGS &&...args) {
  return create_shared<SequencePattern>(std::forward<ARGS>(args)...);
}

template <typename... ARGS> shared_ptr<Pattern> oneof(ARGS &&...args) {
  return create_shared<RankedChoicePattern>(std::forward<ARGS>(args)...);
}

} // namespace rats

#endif
