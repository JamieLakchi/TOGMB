#include "MathParser.h"
#include "declarations.h"
#include "grammarSymbols.h"

namespace calculator {

using namespace rats;

MathParser::MathParser() {
  auto gptr = create_unique<GrammarStorage>();
  auto &g = *gptr;

  auto Statement = g.reserveId();
  auto Evaluate = g.reserveId();
  auto AssignFunction = g.reserveId();
  auto AssignVariable = g.reserveId();

  auto Expr = g.reserveId();
  auto Term = g.reserveId();
  auto Factor = g.reserveId();
  auto Number = g.reserveId();
  auto Variable = g.reserveId();
  auto Function = g.reserveId();

  auto ExprList = g.reserveId();
  auto VariableList = g.reserveId();

  g.attach(ExprList,
           prod(sym::ExprList,
                oneof(seq(var(Expr), term(","), var(ExprList)), var(Expr))));

  g.attach(VariableList,
           prod(sym::VariableList,
                oneof(seq(var(Variable), term(","), var(VariableList)),
                      var(Variable))));

  g.attach(Statement, prod(sym::Statement, var(AssignFunction),
                           var(AssignVariable), oneof(var(Evaluate))));

  g.attach(Evaluate, prod(sym::Evaluate, var(Expr)));
  g.attach(AssignFunction,
           prod(sym::AssignFunction,
                seq(seq(var(Variable), term("("), var(VariableList), term(")")),
                    term("="), var(Expr))));
  g.attach(AssignVariable,
           prod(sym::AssignVariable, seq(var(Variable), term("="), var(Expr))));

  g.attach(Number, prod(sym::Number, num()));
  g.attach(Variable, prod(sym::Variable, vname()));
  g.attach(Function, prod(sym::Function, seq(var(Variable), term("("),
                                             var(ExprList), term(")"))));

  g.attach(Expr, prod(sym::Expr,
                      seq(var(Term),
                          oneof(seq(oneof(term("+"), term("-")), var(Expr)),
                                term("")))));

  g.attach(Term, prod(sym::Term,
                      seq(var(Factor),
                          oneof(seq(oneof(term("*"), term("/")), var(Term)),
                                term("")))));

  g.attach(Factor,
           prod(sym::Factor, oneof(var(Number), var(Function), var(Variable),
                                   seq(term("("), var(Expr), term(")")))));

  g.setStartId(Statement);

  _parser = create_unique<rats::Parser>();

  _parser->setGrammar(std::move(gptr));
}

rats::Parser::ParseResult MathParser::parse(const string &input) {
  return _parser->parse(input);
}

} // namespace calculator
