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
#include <QComboBox>
#include "../declarations.h"

namespace calculator{
    class Calculator;
}
namespace gui {
    class keyboardWindow;
    class menu;
    class functionWindow;
    class variableWindow;
    class base: public QMainWindow {
        Q_OBJECT
    public:
        ~base() override;

        explicit base(QWidget *parent = 0);
    private slots:
        void execute(string f);
        void evaluate();
        void addChar(char c);
        void getKeyboard();
        void getFunctions();
        void getVariables();
        void backspace();
        void reset();
        void addToExpr(std::string f);
        void loadFile(int index);
        void openResetMenu();
        void loadAndReset();
        void load();
        void cancel();
        void openWriteMenu();
        void preWrite();
        void write();
        void overwriteCancel();
        void log();
    signals:
        void function_success(string input);
        void variable_success(string input, string value);
    private:
        void files();
        void disableall();
        void enableall();
        void addexpr(const std::string& expression);
        void update_last(int type, string result, string input);
        QGridLayout *layout;
        QWidget *centralWidget{};
        QPushButton *quitButton;
        QPushButton *evaluateButton;
        QLineEdit *evaluateBox;
        keyboardWindow *keyboard=nullptr;
        functionWindow *functions=nullptr;
        variableWindow *variables=nullptr;
        QListWidget *list;
        QLabel *last_operation;
        QPushButton *logButton;
        QPushButton *keyboardButton;
        QPushButton *resetButton;
        //calc stands for calculator I'm just using slang
        std::unique_ptr<calculator::Calculator> calc;
        QPushButton *functionButton;
        QPushButton *variableButton;
        QPushButton *writeButton;
        QComboBox *selectFile;
        vector<string> filenames{};
        menu *filemenu=nullptr;
        menu *resetmenu=nullptr;
        menu *writemenu=nullptr;
        menu *overwritemenu=nullptr;
        int selected=0;
        std::vector<string> current_log{};

        std::vector<QWidget *> outputs{};
    };

} // gui

#endif //MBGUI_BASE_H
