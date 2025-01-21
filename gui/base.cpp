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
#include "calculator.h"
using namespace gui;

base::base(QWidget *parent): QMainWindow(parent)
        , centralWidget(new QWidget(this))
        , layout(new QGridLayout())
        , calc(std::make_unique<calculator::Calculator>())
        , quitButton(new QPushButton("quit", this))
        , evaluateButton(new QPushButton("=", this))
        , clearButton(new QPushButton("clear", this))
        , functionButton(new QPushButton("functions", this))
        , resetButton(new QPushButton("reset", this))
        , keyboardButton(new QPushButton("keyboard", this))
        , variableButton(new QPushButton("variables", this))
        , last_operation(new QLabel("None\n\n\n\n", this))
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
    layout->addWidget(evaluateBox, 4, 1, 1, 3);
    layout->addWidget(evaluateButton,4,4);
    layout->addWidget(clearButton,1,2);
    layout->addWidget(functionButton,0,1, 1,2);
    layout->addWidget(variableButton,0,3, 1,2);
    layout->addWidget(last_operation,3,2, 1,3);
    layout->addWidget(new QLabel("Last Operation:\n\n\n\n", this),3,1, 1,3);
    list=new QListWidget(this);
    layout->addWidget(list,2,1,1,4);
    //frame=new QFocusFrame(this);
    //setGeometry();
    auto basefuncs=calc->_mem->_funcs;
    functions->add_base(basefuncs);
    auto basevars=calc->_mem->_gvars;
    variables->add_base(basevars);
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
    connect(functions, &functionWindow::addToExpr, this, &base::addToExpr);
    connect(variables, &variableWindow::addToExpr, this, &base::addToExpr);
    connect(functions, &functionWindow::newfunc, this, &base::add_function);
    connect(variables, &variableWindow::newVariable_signal,this, &base::addVariable);
    connect(evaluateBox,&QLineEdit::textChanged,this, &base::dontdothat);
    connect(this, &base::variable_success,variables,&variableWindow::newvaradd);
    connect(this, &base::function_success,functions,&functionWindow::newfuncadd);
    keyboard->setHidden(true);
}

base::~base() {

}

void base::addexpr(const std::string& expression) {
    std::string thing=expression;

    while(thing[thing.size()-1]=='0'){
        thing.pop_back();
    }
    if(thing[thing.size()-1]=='.'){
        thing.pop_back();
    }

    list->addItem(thing.c_str());
}

void base::evaluate() {
    QString thing=evaluateBox->text();
    auto res=calc->enterOperation(thing.toStdString());
    string result=res->_message;
    if(!update_last(int(res->_type),result,0,thing.toStdString())){
        return;
    }
    std::string expression=thing.toStdString()+" = "+result;
    addexpr(expression);
}

void base::addChar(char c) {
    QString text=evaluateBox->text();
    text.push_back(c);
    evaluateBox->setText(text);
}

void base::getKeyboard() {
    keyboard->setHidden(keyboard->isVisible());
}

void base::backspace() {
    std::string text=evaluateBox->text().toStdString();
    text.pop_back();
    evaluateBox->setText(text.c_str());
}

void base::reset() {
    list->clear();
    auto newthing=std::make_unique<calculator::Calculator>();
    calc.swap(newthing);
    auto basefuncs=calc->_mem->_funcs;
    functions->add_base(basefuncs);
    auto basevars=calc->_mem->_gvars;
    variables->add_base(basevars);
    evaluateBox->clear();
    last_operation->setText("None\n\n\n\n");
}

void base::getFunctions() {
    functions->setHidden(functions->isVisible());
}

void base::add_function(std::string f) {
    auto res=calc->enterOperation(f);
    string result=res->_message;
    emit function_success(update_last(int(res->_type),result,1,f), result);
}

void base::addToExpr(std::string f) {
    std::string text=evaluateBox->text().toStdString();
    text+=f;
    evaluateBox->setText(text.c_str());
}

void base::getVariables() {
    variables->setHidden(variables->isVisible());
}

void base::addVariable(std::string f) {
    auto res=calc->enterOperation(f);
    string result=res->_message;

    emit variable_success(update_last(int(res->_type),result,2,f), result);
}

void base::dontdothat(const QString &q) {
    if(!q.contains('=')){
        return;
    }
    backspace();
}

bool base::update_last(int type, string result, int inputtype, string input) {
    string operationstring;
    operationstring+="Input: "+input+"\n";
    switch(type){
        case 0:
            operationstring+="Error: There was an error in parsing\n";
            operationstring+="Message: "+result;
            break;
        case 1:
            operationstring+="Error: Expression invalid\n";
            operationstring+="Message: "+result;
            break;
        default:
            operationstring+="Result: "+result;
    }
    if(result.empty()){
        for(int i=0;i<9;i++){
            operationstring.pop_back();
        }
    }
    operationstring+="\nInput type: ";
    switch(inputtype){
        case 0:
            operationstring+="Expression";
            break;
        case 1:
            operationstring+="Function Assignment";
            break;
        default:
            operationstring+="Variable Assignment";
    }
    int amount=std::count(operationstring.begin(), operationstring.end(),'\n');
    for(int i=0;i<3-amount;i++){
        operationstring+='\n';
    }
    if(type!=inputtype+2){
        operationstring="Success: false\n"+operationstring;
        last_operation->setText(operationstring.c_str());
        return false;
    }
    operationstring="Success: true\n"+operationstring;
    last_operation->setText(operationstring.c_str());
    return true;
}
// gui