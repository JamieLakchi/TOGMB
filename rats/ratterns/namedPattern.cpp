#include "namedPattern.h"
#include <utility>

namespace rats {

NamedPattern::NamedPattern(const string &name, shared_ptr<Pattern> pattern)
    : _name{name}, _pattern{std::move(pattern)} {}

} // namespace rats
