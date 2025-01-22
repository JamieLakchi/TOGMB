//
// Created by roanr on 15/01/2025.
//

#ifndef MBGUI_VARIABLEWINDOW_H
#define MBGUI_VARIABLEWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include "../declarations.h"

class System;
namespace gui {
    class variableWindow: public QWidget {
        Q_OBJECT
        QListWidget *list;
        QLineEdit *varname;
        QLineEdit *varvalue;
        QPushButton *addvar;
    public slots:
        void newVariable_slot();
        void newvaradd(string input, string value);
        void addToBox(QListWidgetItem *item);
    public:
        ~variableWindow() override;
        void add_base(std::unordered_map<string, Number> map);
    public:
        explicit variableWindow(QWidget *parent = 0);

    signals:
        void newVariable_signal(std::string v);
        void addToExpr(std::string f);
    private:
        QGridLayout *layout;
    };

} // gui

#endif //MBGUI_VARIABLEWINDOW_H
