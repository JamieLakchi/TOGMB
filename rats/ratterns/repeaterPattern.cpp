#include "repeaterPattern.h"
#include <utility>

namespace rats {

RepeaterPattern::RepeaterPattern(const size_t min, const size_t max,
                                 shared_ptr<Pattern> pattern)
    : _min{min}, _max{max}, _pattern{std::move(pattern)} {}

} // namespace rats
