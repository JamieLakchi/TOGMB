#ifndef INC_RATS_NAMEDPATTERN
#define INC_RATS_NAMEDPATTERN

#include "declarations.h"
#include "ratterns/pattern.h"

namespace rats {

struct NamedPattern : public Pattern {
  PATTERN
  NamedPattern(const string &name, shared_ptr<Pattern> pattern);

  const string _name;
  shared_ptr<Pattern> _pattern;
};

} // namespace rats

#endif
