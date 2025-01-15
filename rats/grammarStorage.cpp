#include "grammarStorage.h"
#include "assert.h"
#include <utility>

namespace rats {

variableId GrammarStorage::reserveId() {
  auto reserved = ++_ids;

  _patterns[reserved] = nullptr;

  return reserved;
}

void GrammarStorage::attach(const variableId id, shared_ptr<Pattern> pattern) {
  auto found = _patterns.find(id);

  ERR_IF(found == _patterns.end(), NoIdReserved);
  ERR_IF(found->second != nullptr, IdAlreadyInUse);

  found->second = std::move(pattern);
}

shared_ptr<Pattern> &GrammarStorage::get(const variableId id) {
  auto found = _patterns.find(id);

  ERR_IF(found == _patterns.end(), NoIdFound);

  return found->second;
}

void GrammarStorage::setStartId(const variableId id) { _startId = id; }

variableId GrammarStorage::getStartId() const { return _startId; }

} // namespace rats
