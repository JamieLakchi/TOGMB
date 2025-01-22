//
// Created by roanr on 22/01/2025.
//

#include <QPushButton>
#include <iostream>
#include "menu.h"
#include "base.h"

namespace gui {
    menu::menu(std::string question, std::vector<std::string> options,bool hasTextBox, QWidget *parent): QWidget(parent)
            , layout(new QGridLayout())
    {
        setWindowFlags(Qt::Window | Qt::WindowTitleHint);
        layout->addWidget(new QLabel(question.c_str()),0,1,1,options.size());
        if(hasTextBox){
            textBox=new QLineEdit(this);
            layout->addWidget(textBox,1,1,1,options.size());
        }
        QWidget::setWindowTitle("Menu");
        for(int i=0;i<options.size();i++){
            auto option=options[i];
            auto button=new QPushButton(option.c_str(), this);
            layout->addWidget(button,2,i+1);
            buttons.push_back(button);
        }
        setLayout(layout);
    }
} // gui