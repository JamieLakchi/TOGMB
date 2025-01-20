#ifndef INC_CALCULATOR_ASTEVALUATOR
#define INC_CALCULATOR_ASTEVALUATOR

#include "declarations.h"

namespace calculator {

class CalculatorMemory;
struct ASTNode;

class ASTEvaluator {
public:
  Number evaluate(CalculatorMemory &m, shared_ptr<ASTNode> ast);

private:
};

} // namespace calculator

#endif
