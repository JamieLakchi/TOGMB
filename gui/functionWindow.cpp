//
// Created by roanr on 15/01/2025.
//

#include <QLabel>
#include <fstream>
#include <QListWidgetItem>
#include <iostream>
#include "functionWindow.h"
#include "base.h"
#include "calculator.h"

namespace gui {
    functionWindow::functionWindow(QWidget *parent) : QWidget(parent)
            , layout(new QGridLayout())
            , funcname(new QLineEdit(this))
            , funcparams(new QLineEdit(this))
            , funcdef(new QLineEdit(this))
            , addfunc(new QPushButton("add",this))
            , list(new QListWidget(this))
    {
        layout->addWidget(list,1,1,1,2);
        layout->addWidget(new QLabel("function name: "), 2, 1);
        layout->addWidget(new QLabel("function parameters: "), 3, 1);
        layout->addWidget(new QLabel("function definition: "), 4, 1);
        layout->addWidget(addfunc, 5, 1, 1,2);
        layout->addWidget(funcname, 2, 2);
        layout->addWidget(funcparams, 3, 2);
        layout->addWidget(funcdef, 4, 2);
        setLayout(layout);
        setHidden(true);
        QWidget::setWindowTitle("Functions");
        setWindowFlags(Qt::Window | Qt::WindowTitleHint);
        load_base();
        connect(list, &QListWidget::itemClicked,this, &functionWindow::addToBox);
        connect(addfunc,SIGNAL(clicked()),this,SLOT(add_function()));
    }

    void functionWindow::load_base() {
        //TODO probably delete
        std::ifstream base("base_functions.txt");
        if (!base.is_open()) {return;}
        std::cout<<"hahah";
        std::string line;
        while(std::getline(base,line)){
            list->addItem(new QListWidgetItem(line.c_str()));
            emit newfunc(line);
        }
    }

    void functionWindow::add_function() {
        std::string f;
        f+=funcname->text().toStdString()+"(";
        funcname->clear();
        f+=funcparams->text().toStdString()+")=";
        funcparams->clear();
        f+=funcdef->text().toStdString();
        funcdef->clear();
        emit newfunc(f);
    }

    void functionWindow::addToBox(QListWidgetItem *item) {
        std::string f=item->text().toStdString();
        f=f.substr(0,f.find('='));
        emit addToExpr(f);
    }

    void functionWindow::add_base(
            std::unordered_map<string, calculator::CalculatorMemory::FunctionScopeEntry> funcs) {
        //hashmap<string, shared_ptr<ASTNode>> funcs;
        list->clear();
        //funcs=system->getVariables();
        std::vector<string> not_in_window{"+","-","*","/","Neg"};
        for(const auto &funcpair:funcs){
            if(std::find(not_in_window.begin(), not_in_window.end(),funcpair.first)!=not_in_window.end()){
                continue;
            }
            auto func=funcpair.second;
            string thing= funcpair.first+"(";
            for(char i='a';i<'a'+funcpair.second._varCount;i++){
                thing+=i;
                thing+=", ";
            }if(funcpair.second._varCount>0){thing.pop_back();thing.pop_back();}
            thing+=") = "+funcpair.second._definition;

            list->addItem(new QListWidgetItem(thing.c_str()));
        }
    }

    void functionWindow::newfuncadd(string s) {
        list->addItem(new QListWidgetItem(s.c_str()));
    }
} // gui