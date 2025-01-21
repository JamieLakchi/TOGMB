//
// Created by roanr on 14/01/2025.
//

#ifndef MBGUI_BASE_H
#define MBGUI_BASE_H
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QString>
#include <QLineEdit>
#include <QFocusFrame>
#include <QLabel>
#include "../declarations.h"

namespace calculator{
    class Calculator;
}
namespace gui {
    class keyboardWindow;
    class functionWindow;
    class variableWindow;
    class base: public QMainWindow {
        Q_OBJECT
    public:
        ~base() override;

        explicit base(QWidget *parent = 0);
    private slots:
        void evaluate();
        void addChar(char c);
        void getKeyboard();
        void getFunctions();
        void getVariables();
        void backspace();
        void reset();
        void add_function(std::string f);
        void addToExpr(std::string f);
        void addVariable(std::string f);
        void dontdothat(const QString &q);
    signals:
        void function_success(bool b, string s);
        void variable_success(bool b, string s);
    private:
        void addexpr(const std::string& expression);
        bool update_last(int type, string result, int inputtype, string input);
        QGridLayout *layout;
        QWidget *centralWidget{};
        //QFocusFrame *frame;
        QPushButton *quitButton;
        QPushButton *evaluateButton;
        QLineEdit *evaluateBox;
        keyboardWindow *keyboard=nullptr;
        functionWindow *functions=nullptr;
        variableWindow *variables=nullptr;
        QListWidget *list;
        QLabel *last_operation;
        QPushButton *clearButton;
        QPushButton *keyboardButton;
        QPushButton *resetButton;
        //calc stands for calculator I'm just using slang
        std::unique_ptr<calculator::Calculator> calc;
        long double last_result=0;
        QPushButton *functionButton;
        QPushButton *variableButton;
    };

} // gui

#endif //MBGUI_BASE_H
