//
// Created by roanr on 15/01/2025.
//

#ifndef MBGUI_FUNCTIONWINDOW_H
#define MBGUI_FUNCTIONWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <unordered_map>
#include "calculator.h"

namespace calculator{
class Calculator;
}
namespace gui {

    class functionWindow: public QWidget {
        Q_OBJECT

        QListWidget *list;
        QLineEdit *funcname;
        QLineEdit *funcparams;
        QGridLayout *layout;
        std::string last;
        void load_base();
    public slots:
        void add_function();
        void addToBox(QListWidgetItem *item);
        void newfuncadd(bool b, string s);
    signals:
        void newfunc(std::string f);
        void addToExpr(std::string f);
    public:
        functionWindow(QWidget *parent = 0);
        void add_base(std::unordered_map<string, calculator::CalculatorMemory::FunctionScopeEntry> funcs);

        QPushButton *addfunc;
        QLineEdit *funcdef;
    };

} // gui

#endif //MBGUI_FUNCTIONWINDOW_H
