//
// Created by roanr on 14/01/2025.
//

#include <QApplication>
#include <QLabel>
#include <QListWidget>
#include <sstream>
#include "base.h"
#include "keyboardWindow.h"
#include "functionWindow.h"
#include "variableWindow.h"
#include "../calculator/calculator.h"
using namespace gui;

base::base(QWidget *parent): QMainWindow(parent)
        , centralWidget(new QWidget(this))
        , layout(new QGridLayout())
        , quitButton(new QPushButton("quit", this))
        , evaluateButton(new QPushButton("=", this))
        , clearButton(new QPushButton("clear", this))
        , functionButton(new QPushButton("functions", this))
        , resetButton(new QPushButton("reset", this))
        , keyboardButton(new QPushButton("keyboard", this))
        , variableButton(new QPushButton("variables", this))
        , evaluateBox(new QLineEdit(this))
        , keyboard(new keyboardWindow())
        , functions(new functionWindow())
        , variables(new variableWindow())
{
    QWidget::setWindowTitle("Main window");
    setFixedSize(500,500);
    //quitButton->setPalette(QPalette(QColor("White")));
    setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    layout->addWidget(quitButton, 1, 4);
    layout->addWidget(keyboardButton, 1, 1);
    layout->addWidget(resetButton, 1, 3);
    layout->addWidget(evaluateBox, 3, 1, 1, 3);
    layout->addWidget(evaluateButton,3,4);
    layout->addWidget(clearButton,1,2);
    layout->addWidget(functionButton,0,1, 1,2);
    layout->addWidget(variableButton,0,3, 1,2);
    list=new QListWidget(this);
    layout->addWidget(list,2,1,1,4);
    //frame=new QFocusFrame(this);
    //setGeometry();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    showMaximized();
    connect(quitButton, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
    connect(evaluateButton, SIGNAL(clicked()), this, SLOT(evaluate()));
    connect(keyboard->evaluate, SIGNAL(clicked()), this, SLOT(evaluate()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(functionButton, SIGNAL(clicked()), this, SLOT(getFunctions()));
    connect(clearButton, SIGNAL(clicked()), list, SLOT(clear()));
    connect(keyboardButton, SIGNAL(clicked()), this, SLOT(getKeyboard()));
    connect(variableButton, SIGNAL(clicked()), this, SLOT(getVariables()));
    connect(keyboard->clear, SIGNAL(clicked()), evaluateBox, SLOT(clear()));
    connect(keyboard, &keyboardWindow::character_signal, this, &base::addChar);
    connect(keyboard->backspace, SIGNAL(clicked()), this, SLOT(backspace()));
    connect(functions, &functionWindow::addToExpr, this, &base::addFunctionToExpr);
    connect(variables, &variableWindow::newVariable_signal,this, &base::addVariable);
    keyboard->setHidden(true);
}

base::~base() {

}

void base::addexpr(const std::string& expression) {
    std::string thing=expression;
    //std::string thing=latest.toStdString()+" = "+std::to_string(t->eval());
    /*
    while(thing[thing.size()-1]=='0'){
        thing.pop_back();
    }
    if(thing[thing.size()-1]=='.'){
        thing.pop_back();
    }
     */
    list->addItem(thing.c_str());
    //layout->addWidget(new QLabel(thing.c_str(), this));
}

void base::evaluate() {
    QString thing=evaluateBox->text();
    latest=thing;
    //evaluateBox->clear();
    //addtotheshit
    /*
    calculator::Calculator calculator1;
    calculator1.enterOperation()
    auto newexpr=new Expression(thing.toStdString());
    addexpr(newexpr);
     */
    Number result=0;
    std::stringstream blah;
    blah << result;
    std::string expression=latest.toStdString()+" = "+blah.str();
    addexpr(expression);
}

void base::addChar(char c) {
    QString text=evaluateBox->text();
    text.push_back(c);
    evaluateBox->setText(text);
}

void base::getKeyboard() {
    keyboard->setHidden(keyboard->isVisible());
    //keyboard->show();
}

void base::backspace() {
    std::string text=evaluateBox->text().toStdString();
    text.pop_back();
    evaluateBox->setText(text.c_str());
}

void base::reset() {
    list->clear();
    //TODO: reset lmao
}

void base::getFunctions() {
    functions->setHidden(functions->isVisible());
}

void base::add_function(std::string f) {
    //TODO: actually add it
    //functions->update(bridge.somefunction())
}

void base::addFunctionToExpr(std::string f) {
    std::string text=evaluateBox->text().toStdString();
    text+=f;
    evaluateBox->setText(text.c_str());
}

void base::getVariables() {
    variables->setHidden(variables->isVisible());
}

void base::addVariable(std::string f) {
    //TODO: actually add it
    //variables->update(bridge.somefunction())
}
// gui