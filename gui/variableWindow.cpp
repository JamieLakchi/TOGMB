//
// Created by roanr on 15/01/2025.
//

#include <QLabel>
#include <QLineEdit>
#include "variableWindow.h"

namespace gui {
    void variableWindow::update(const std::map<std::string, Number>& variables) {
        list->clear();
        //variables=system->getVariables();
        for(const auto &variable_pair:variables){
            //auto variable=variable_pair.second;
            string thing= variable_pair.first + std::to_string(variable_pair.second);
            list->addItem(new QListWidgetItem(thing.c_str()));
        }
    }

    void variableWindow::newVariable_slot() {
        std::string v;
        v+= varname->text().toStdString() + "=";
        varname->clear();
        v+=varvalue->text().toStdString();
        varvalue->clear();
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
    }

    variableWindow::~variableWindow() {

    }
} // gui