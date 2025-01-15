#include "ratterns.h"
#include "declarations.h"

namespace rats {

shared_ptr<Pattern> term(const string &literal) {
  return create_shared<LiteralPattern>(literal);
}

shared_ptr<Pattern> var(const patternId id) {
  return create_shared<VariablePattern>(id);
}

shared_ptr<Pattern> rep(const size_t min, const size_t max,
                        shared_ptr<Pattern> pattern) {
  return create_shared<RepeaterPattern>(min, max, pattern);
}

shared_ptr<Pattern> num() { return create_shared<NumberPattern>(); }

shared_ptr<Pattern> named(const string &name, shared_ptr<Pattern> pattern) {
  return create_shared<NamedPattern>(name, pattern);
}

shared_ptr<Pattern> vname() { return create_shared<VarNamePattern>(); }

} // namespace rats
