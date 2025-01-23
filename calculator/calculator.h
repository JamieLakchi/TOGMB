#ifndef INC_CALCULATOR_CALCULATOR
#define INC_CALCULATOR_CALCULATOR

#include "ASTConverter.h"
#include "ASTEvaluator.h"
#include "MathParser.h"
#include "declarations.h"
#include "parseTreeNode.h"
#include <functional>
namespace gui {
class base;
}
namespace calculator {

struct CalculatorMemory {
  // variables memory
  using scope = hashmap<string, Number>;
  scope _gvars; // global scope

  struct LocalVarStackElem {
    LocalVarStackElem(shared_ptr<LocalVarStackElem> prev);

    scope _lvars;                        // local scope
    shared_ptr<LocalVarStackElem> _prev; // previous scope
  };

  shared_ptr<LocalVarStackElem> _lvars =
      nullptr; // the function scopes form a stack, each function will be
               // responsible for placing and removing it's own scope

  // helper func, nullptr means not found
  Number *findVar(const string &name);

  // function memory
  using CalcFunction = std::function<Number(CalculatorMemory &)>;

  struct FunctionScopeEntry {
    FunctionScopeEntry() = default;
    FunctionScopeEntry(CalcFunction func, size_t varCount,
                       const string &definition);

    CalcFunction _func;
    size_t _varCount;
    string _definition;
  };

  using fscope = hashmap<string, FunctionScopeEntry>;
  fscope _funcs; // function memory

  // parameters
  vector<Number> _args;
};

class Calculator {
  friend class gui::base;

public:
  Calculator();

  struct OperationResult {
    enum class Type {
      ParseError,
      InvalidExpression,
      Evaluation,     // value
      FunctionAssign, // *empty*
      VariableAssign, // value
    };

    OperationResult() = default;
    OperationResult(Type type, const string &message);

    Type _type;
    string _message;
    shared_ptr<rats::ParseTreeNode> _parseTree = nullptr;
    shared_ptr<calculator::ASTNode> _ast = nullptr;
  };

  shared_ptr<OperationResult> enterOperation(const string &input);

private:
  // helpers
  // create OperationResult
  shared_ptr<OperationResult> cOR(OperationResult::Type type,
                                  const string &message);
  // create CalculatorMemory::LocalVarStackElem
  shared_ptr<CalculatorMemory::LocalVarStackElem>
  cLS(shared_ptr<CalculatorMemory::LocalVarStackElem> &prev);

  // parsing
  unique_ptr<MathParser> _parser;
  unique_ptr<ASTConverter> _toAST;

  // evaluating

  // memory
  unique_ptr<CalculatorMemory> _mem;

  // AST evaluation
  unique_ptr<ASTEvaluator> _eval;

  // AST validation
  shared_ptr<OperationResult> validate(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_FunctionAssign(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_VariableAssign(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_Evaluation(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_Operation(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_Number(shared_ptr<ASTNode> &root);

  shared_ptr<OperationResult> v_Variable(shared_ptr<ASTNode> &root);
};

} // namespace calculator

#endif
