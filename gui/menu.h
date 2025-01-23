//
// Created by roanr on 22/01/2025.
//

#ifndef MBTOG_MENU_H
#define MBTOG_MENU_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>

namespace gui {
    class base;
    class menu: public QWidget {
        Q_OBJECT
        //QComboBox *widget;
    public:
        explicit menu(std::string question, std::vector<std::string> options,bool asList=false,bool hasTextBox = false,QWidget *parent = 0);
        std::vector<QPushButton*>buttons{};
        QGridLayout *layout;
        QLineEdit *textBox;
        QListWidget *list;
    };

} // gui

#endif //MBTOG_MENU_H
