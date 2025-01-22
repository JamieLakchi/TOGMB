//
// Created by roanr on 22/01/2025.
//

#ifndef MBTOG_MENU_H
#define MBTOG_MENU_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

namespace gui {
    class base;
    class menu: public QWidget {
        Q_OBJECT
        //QComboBox *widget;
    public:
        explicit menu(std::string question, std::vector<std::string> options,bool hasTextBox = false,QWidget *parent = 0);
        std::vector<QPushButton*>buttons{};
        QGridLayout *layout;
        QLineEdit *textBox;
    };

} // gui

#endif //MBTOG_MENU_H
