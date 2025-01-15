#include "MathParser.h"
#include <algorithm>
#include <utility>

using namespace calculator;

int main(int argc, char *argv[]) {

  MathParser p;

  auto ans = p.parse("f(x,m)=956.98*5+(varrr-0984.777)-f(0.96*3.14,5)*3");

  rats::GraphvizTool gt{};

  if (ans._success) {
    std::cout << "success" << std::endl;
    gt.createDotFile("output/graph.txt", ans._ans);
  } else {
    std::cout << "failure" << std::endl;
    if (ans._ans) {
      std::cout << "yield: " << ans._ans->yield() << std::endl;
      gt.createDotFile("output/graph.txt", ans._ans);
    }
  }
  return 0;
}
