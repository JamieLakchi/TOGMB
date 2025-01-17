//
// Created by roanr on 14/01/2025.
//

#ifndef MBGUI_KEYBOARDWINDOW_H
#define MBGUI_KEYBOARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

namespace gui {

    class keyboardWindow: public QWidget {
        Q_OBJECT
        QGridLayout *layout;
    private slots:
        void plus_slot();
        void minus_slot();
        void divide_slot();
        void multiply_slot();
        void zero_slot();
        void one_slot();
        void two_slot();
        void three_slot();
        void four_slot();
        void five_slot();
        void six_slot();
        void seven_slot();
        void eight_slot();
        void nine_slot();
        void decimal_slot();
        void left_slot();
        void right_slot();
    signals:
        void character_signal(char c);
    public:
        QPushButton *plus;
        QPushButton *minus;
        QPushButton *divide;
        QPushButton *multiply;
        QPushButton *zero;
        QPushButton *one;
        QPushButton *two;
        QPushButton *three;
        QPushButton *four;
        QPushButton *five;
        QPushButton *six;
        QPushButton *seven;
        QPushButton *eight;
        QPushButton *nine;
        QPushButton *decimal;
        QPushButton *backspace;
        explicit keyboardWindow(QWidget *parent = 0);
        QPushButton *left;
        QPushButton *right;
        QPushButton *clear;
        QPushButton *evaluate;
    };

} // gui

#endif //MBGUI_KEYBOARDWINDOW_H
