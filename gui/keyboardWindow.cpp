//
// Created by roanr on 14/01/2025.
//

#include "keyboardWindow.h"

namespace gui {
    keyboardWindow::keyboardWindow(QWidget *parent): QWidget(parent)
            , layout(new QGridLayout())
            , zero(new QPushButton("0", this))
            , one(new QPushButton("1", this))
            , two(new QPushButton("2", this))
            , three(new QPushButton("3", this))
            , four(new QPushButton("4", this))
            , five(new QPushButton("5", this))
            , six(new QPushButton("6", this))
            , seven(new QPushButton("7", this))
            , eight(new QPushButton("8", this))
            , nine(new QPushButton("9", this))
            , plus(new QPushButton("+", this))
            , minus(new QPushButton("-", this))
            , divide(new QPushButton("/", this))
            , multiply(new QPushButton("*", this))
            , decimal(new QPushButton(".", this))
            , clear(new QPushButton("clear", this))
            , backspace(new QPushButton("<-", this))
            , left(new QPushButton("(", this))
            , right(new QPushButton(")", this))
            , evaluate(new QPushButton("=", this))
    {
        QWidget::setWindowTitle("Keyboard");
        layout->addWidget(zero, 4, 2);
        layout->addWidget(one, 3, 1);
        layout->addWidget(two, 3, 2);
        layout->addWidget(three, 3, 3);
        layout->addWidget(four, 2, 1);
        layout->addWidget(five, 2, 2);
        layout->addWidget(six, 2, 3);
        layout->addWidget(seven, 1, 1);
        layout->addWidget(eight, 1, 2);
        layout->addWidget(nine, 1, 3);
        layout->addWidget(plus, 1, 4);
        layout->addWidget(multiply, 3, 4);
        layout->addWidget(divide, 4, 4);
        layout->addWidget(minus, 2, 4);
        //layout->addWidget(hide, 0, 5);
        layout->addWidget(decimal, 4, 1);
        layout->addWidget(backspace, 0, 3);
        layout->addWidget(left, 0, 1);
        layout->addWidget(right, 0, 2);
        layout->addWidget(clear, 0, 4);
        layout->addWidget(evaluate, 4, 3);
        setLayout(layout);
        setWindowFlags(Qt::Window | Qt::WindowTitleHint);
        connect(zero, SIGNAL(clicked()),this,SLOT(zero_slot()));
        connect(one, SIGNAL(clicked()),this,SLOT(one_slot()));
        connect(two, SIGNAL(clicked()),this,SLOT(two_slot()));
        connect(three, SIGNAL(clicked()),this,SLOT(three_slot()));
        connect(four, SIGNAL(clicked()),this,SLOT(four_slot()));
        connect(five, SIGNAL(clicked()),this,SLOT(five_slot()));
        connect(six, SIGNAL(clicked()),this,SLOT(six_slot()));
        connect(seven, SIGNAL(clicked()),this,SLOT(seven_slot()));
        connect(eight, SIGNAL(clicked()),this,SLOT(eight_slot()));
        connect(nine, SIGNAL(clicked()),this,SLOT(nine_slot()));
        connect(plus, SIGNAL(clicked()),this,SLOT(plus_slot()));
        connect(minus, SIGNAL(clicked()),this,SLOT(minus_slot()));
        connect(multiply, SIGNAL(clicked()),this,SLOT(multiply_slot()));
        connect(divide, SIGNAL(clicked()),this,SLOT(divide_slot()));
        connect(decimal, SIGNAL(clicked()),this,SLOT(decimal_slot()));
        connect(left, SIGNAL(clicked()),this,SLOT(left_slot()));
        connect(right, SIGNAL(clicked()),this,SLOT(right_slot()));
    }

    void keyboardWindow::plus_slot() {
        emit character_signal('+');
    }

    void keyboardWindow::minus_slot() {
        emit character_signal('-');
    }

    void keyboardWindow::divide_slot() {
        emit character_signal('/');
    }

    void keyboardWindow::multiply_slot() {
        emit character_signal('*');
    }

    void keyboardWindow::zero_slot() {
        emit character_signal('0');
    }

    void keyboardWindow::one_slot() {
        emit character_signal('1');
    }

    void keyboardWindow::two_slot() {
        emit character_signal('2');
    }

    void keyboardWindow::three_slot() {
        emit character_signal('3');
    }

    void keyboardWindow::four_slot() {
        emit character_signal('4');
    }

    void keyboardWindow::five_slot() {
        emit character_signal('5');
    }

    void keyboardWindow::six_slot() {
        emit character_signal('6');
    }

    void keyboardWindow::seven_slot() {
        emit character_signal('7');
    }

    void keyboardWindow::eight_slot() {
        emit character_signal('8');
    }

    void keyboardWindow::nine_slot() {
        emit character_signal('9');
    }

    void keyboardWindow::decimal_slot() {
        emit character_signal('.');
    }

    void keyboardWindow::left_slot() {
        emit character_signal('(');
    }

    void keyboardWindow::right_slot() {
        emit character_signal(')');
    }
} // gui