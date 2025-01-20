#include "ASTConverter.h"
#include "MathParser.h"
#include "calculator.h"
#include "declarations.h"
#include "parseTreeNode.h"
#include "parser.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace calculator;

int main(int argc, char *argv[]) {
  MathParser p;

  // auto ans = p.parse( "5.12-12.5");
  // auto ans = p.parse("5+a*2-(5+3.1/2)");
  // auto ans = p.parse("newvar=w*(h/b)+2.71");
  // auto ans =
  // p.parse("f(x,m)=956.98*5+(varrr-0984.777)-f(0.96*3.14,5,(50/3*var))*3");
  // auto ans = p.parse("-f(x,m)");
  auto ans = p.parse("f(x)=-2*y+(log(y)+1.1.1)");

  GraphvizTool gt{};
  ASTConverter astc;

  if (ans._success) {
    std::cout << "success" << std::endl;

    gt.createDotFile("output/PTGraph.txt", ans._ans);
    auto ast = astc.convert(ans._ans);

    if (ast) {
      std::cout << "ast success" << std::endl;
      gt.createDotFile("output/ASTGraph.txt", ast);
    }
  } else {
    std::cout << "failure" << std::endl;
    if (ans._ans) {
      std::cout << "yield: " << ans._ans->yield() << std::endl;
      gt.createDotFile("output/graph.txt", ans._ans);
    }
  }

  Calculator c;

  std::vector<string> operations{"a=5",
                                 "b=5",
                                 "a+b",
                                 "f(x)=x",
                                 "f(-2)",
                                 "-()",
                                 "f(x,y)=+2-5+++3",
                                 "g(x)=sin(x)/cos(x)",
                                 "g(pi)",
                                 "g(pi/2)",
                                 "v(x,)=3",
                                 "",
                                 "f(x)=-2*y+(log(y)+1.1.1)"};

  for (auto &elem : operations) {
    auto result = c.enterOperation(elem);
    std::cout << (int)result->_type << " " << result->_message << std::endl;
  }

  std::cout << "now using std::cin" << std::endl;

  while (true) {
    string operation;
    getline(std::cin, operation);
    auto result = c.enterOperation(operation);
    std::cout << (int)result->_type << " " << result->_message << std::endl;
  }

  return 0;
}
