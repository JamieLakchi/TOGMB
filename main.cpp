#include "rats.h"
#include <algorithm>
#include <utility>

using namespace rats;

int main(int argc, char *argv[]) {
  auto gptr = create_unique<GrammarStorage>();
  auto &g = *gptr;

  auto Expr = g.reserveId();
  auto Term = g.reserveId();
  auto Factor = g.reserveId();

  g.attach(Expr, prod("expression",
                      seq(var(Term),
                          rep(0, Reps::INF,
                              seq(oneof(term("+"), term("-")), var(Term))))));

  g.attach(Term, prod("term",
                      seq(var(Factor),
                          rep(0, Reps::INF,
                              seq(oneof(term("*"), term("/")), var(Factor))))));

  g.attach(Factor, prod("factor", oneof(named("number", num()),
                                        seq(term("("), var(Expr), term(")")))));

  g.setStartId(Expr);

  Parser p;

  p.setGrammar(std::move(gptr));

  auto ans = p.parse("956.98+(5-0984.777)-0.89");

  if (ans) {
    std::cout << "success" << std::endl;
    GraphvizTool gt{};
    gt.createDotFile("output/graph.txt", ans);
  } else {
    std::cout << "failure" << std::endl;
  }

  return 0;
}
