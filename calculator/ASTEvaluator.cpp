#include "ASTEvaluator.h"
#include "calculator.h"
#include <utility>

namespace calculator {

Number ASTEvaluator::evaluate(CalculatorMemory &m, shared_ptr<ASTNode> ast) {
  switch (ast->type) {
  case ASTNode::Type::Number: {
    auto &info = ast->number;
    return info.value;
  } break;
  case ASTNode::Type::Variable: {
    auto &info = ast->variable;
    auto found = m.findVar(info.name);
    return *found;
  } break;
  case ASTNode::Type::Operation: {
    auto &info = ast->operation;
    vector<Number> args;
    for (size_t i = 0; i < info.variables.size(); ++i) {
      args.push_back(evaluate(m, info.variables[i]));
    }
    m._args = std::move(args);
    auto found = m._funcs.find(info.signature);
    return found->second._func(m);
  } break;
  default:
    throw "Evaluator got bad type";
    break;
  }

  return 0;
}

} // namespace calculator
