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
    private slots:
        void newVariable_slot();
    public:
        ~variableWindow() override;

    private:
        void update(const std::map<std::string, Number>& variables);

    public:
        explicit variableWindow(QWidget *parent = 0);

    signals:
        void newVariable_signal(std::string v);
    private:
        QGridLayout *layout;
    };

} // gui

#endif //MBGUI_VARIABLEWINDOW_H
