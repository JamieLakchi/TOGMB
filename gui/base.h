//
// Created by roanr on 14/01/2025.
//

#ifndef MBGUI_BASE_H
#define MBGUI_BASE_H
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QFocusFrame>
#include "../declarations.h"
/*
struct Expression{
    std::string toString(bool with_parameters){
        std::string return_value="f(";
        if(with_parameters){
            return_value+="x, y";
        }
        return_value+=")";
        return return_value;
    }
    long double eval(){return 0;}
    std::string myexpr;
    explicit Expression(std::string s): myexpr(s){}
};
*/
namespace gui {
    class keyboardWindow;
    class functionWindow;
    class variableWindow;
    class base: public QMainWindow {
        Q_OBJECT
    public:
        virtual ~base();

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
        void addFunctionToExpr(std::string f);
        void addVariable(std::string f);
    private:
        void addexpr(const std::string& expression);
        QGridLayout *layout;
        QWidget *centralWidget{};
        //QFocusFrame *frame;
        QPushButton *quitButton;
        QPushButton *evaluateButton;
        QLineEdit *evaluateBox;
        keyboardWindow *keyboard=nullptr;
        functionWindow *functions=nullptr;
        variableWindow *variables=nullptr;
        QString latest;
        QListWidget *list;
        QPushButton *clearButton;
        QPushButton *keyboardButton;
        QPushButton *resetButton;
        long double last_result;
        //TODO: bridge
        QPushButton *functionButton;
        QPushButton *variableButton;
    };

} // gui

#endif //MBGUI_BASE_H
