#include "ASTConverter.h"
#include "MathParser.h"
#include "calculator.h"
#include "gui/base.h"
#include <QApplication>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
using namespace calculator;

/*
int main(int argc, char *argv[]) {

MathParser p;

// auto ans = p.parse( "5.12-12.5");
// auto ans = p.parse("5+a*2-(5+3.1/2)");
auto ans = p.parse("newvar=w*(h/b)+2.71");
// auto ans = p.parse("f(x,m)=956.98*5+(varrr-0984.777)-f(0.96*3.14,5)*3");

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

while (true) {
  string a;
  getline(std::cin, a);
  auto result = c.enterOperation(a);
  std::cout << (int)result->_type << " " << result->_message << std::endl;
}
return 0;
}

*/
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  gui::base mygui;
    app.setWindowIcon(QIcon("guimages/img.png"));
    app.setPalette(QPalette(QColor("lightGray")));
    app.setFont(QFont("OldEnglish"));
  return app.exec();
}
