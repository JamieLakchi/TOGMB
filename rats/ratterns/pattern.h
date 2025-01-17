#ifndef INC_RATS_PATTERN
#define INC_RATS_PATTERN

#include "../../declarations.h"
#include "../parseTreeNode.h"
#include "../parser.h"

namespace rats {
struct Pattern {
  Pattern();

  virtual shared_ptr<ParseTreeNode> eval(Parser &parser) = 0;

  patternId _PId;

  static patternId _PIdCounter;

#define PATTERN                                                                \
  virtual shared_ptr<ParseTreeNode> eval(Parser &parser) override {            \
    return parser.match(*this);                                                \
  };
};

} // namespace rats

#endif
