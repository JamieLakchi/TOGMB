#ifndef INC_RATS_GRAMMARSTORAGE
#define INC_RATS_GRAMMARSTORAGE

#include "../assert.h"
#include "../declarations.h"
#include "ratterns/ratterns.h"

namespace rats {

ERR_CREATE(NoIdReserved, "Tried to attach pattern to id that wasn't reserved.")
ERR_CREATE(NoIdFound, "Tried to find pattern of id that isn't in the grammar.")
ERR_CREATE(IdAlreadyInUse,
           "Tried to attach pattern to id that is already in use.")

class GrammarStorage {
public:
  variableId reserveId();

  void attach(const variableId id, shared_ptr<Pattern> pattern);

  shared_ptr<Pattern> &get(const variableId id);

  void setStartId(const variableId id);

  patternId getStartId() const;

private:
  variableId _ids{0};
  variableId _startId{0};
  hashmap<variableId, shared_ptr<Pattern>> _patterns;
};

template <typename... ARGS>
shared_ptr<Pattern> prod(const string &name, ARGS &&...args) {
  return named(name, oneof(std::forward<ARGS>(args)...));
}

} // namespace rats

#endif
