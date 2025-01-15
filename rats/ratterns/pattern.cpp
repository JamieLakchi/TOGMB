#include "pattern.h"

namespace rats {

patternId Pattern::_PIdCounter = 0;

Pattern::Pattern() : _PId{++_PIdCounter} {}

} // namespace rats
