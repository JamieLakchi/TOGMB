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
        void load_base();
        void update(calculator::Calculator *calculator);
    private slots:
        void add_function();
        void addToBox(QListWidgetItem *item);
    signals:
        void newfunc(std::string f);
        void addToExpr(std::string f);
    public:
        functionWindow(QWidget *parent = 0);

        QPushButton *addfunc;
        QLineEdit *funcdef;
    };

} // gui

#endif //MBGUI_FUNCTIONWINDOW_H
