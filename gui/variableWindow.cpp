//
// Created by roanr on 15/01/2025.
//

#include <QLabel>
#include <QLineEdit>
#include "variableWindow.h"

namespace gui {
    void variableWindow::newVariable_slot() {
        std::string v;
        v+= varname->text().toStdString() + "=";
        v+=varvalue->text().toStdString();
        varvalue->clear();
        varname->clear();
        emit newVariable_signal(v);
    }

    variableWindow::variableWindow(QWidget *parent) : QWidget(parent)
            , layout(new QGridLayout())
            , varname(new QLineEdit(this))
            , varvalue(new QLineEdit(this))
            , addvar(new QPushButton("add",this))
            , list(new QListWidget(this)){
        layout->addWidget(list,1,1,1,2);
        layout->addWidget(varname,2,2,1,1);
        layout->addWidget(varvalue,3,2,1,1);
        layout->addWidget(addvar,4,1,1,2);
        layout->addWidget(new QLabel("name", this),2,1,1,1);
        layout->addWidget(new QLabel("value", this),3,1,1,1);
        setLayout(layout);
        setHidden(true);
        QWidget::setWindowTitle("Variables");
        setWindowFlags(Qt::Window | Qt::WindowTitleHint);
        connect(addvar,SIGNAL(clicked()),this,SLOT(newVariable_slot()));
        connect(list, &QListWidget::itemClicked,this, &variableWindow::addToBox);

    }

    variableWindow::~variableWindow() {

    }

    void variableWindow::add_base(std::unordered_map<string, Number> map) {
        list->clear();
        for(const auto &variable_pair:map){
            string thing= variable_pair.first +" = "+ std::to_string(variable_pair.second);
            list->addItem(new QListWidgetItem(thing.c_str()));
        }
    }

    void variableWindow::newvaradd(string input, string value) {
        std::string v=input.substr(0,input.find('='));
        v+=" = "+value;
        while(v[v.size()-1]=='0'){
            v.pop_back();
        }
        if(v[v.size()-1]=='.'){
            v.pop_back();
        }
        list->addItem(new QListWidgetItem(v.c_str()));
    }

    void variableWindow::addToBox(QListWidgetItem *item) {
        std::string f=item->text().toStdString();
        f=f.substr(0,f.find('='));
        emit addToExpr(f);
    }
} // gui