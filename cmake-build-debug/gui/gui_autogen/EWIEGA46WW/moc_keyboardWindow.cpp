/****************************************************************************
** Meta object code from reading C++ file 'keyboardWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../gui/keyboardWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboardWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gui__keyboardWindow_t {
    QByteArrayData data[21];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui__keyboardWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui__keyboardWindow_t qt_meta_stringdata_gui__keyboardWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "gui::keyboardWindow"
QT_MOC_LITERAL(1, 20, 16), // "character_signal"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 1), // "c"
QT_MOC_LITERAL(4, 40, 9), // "plus_slot"
QT_MOC_LITERAL(5, 50, 10), // "minus_slot"
QT_MOC_LITERAL(6, 61, 11), // "divide_slot"
QT_MOC_LITERAL(7, 73, 13), // "multiply_slot"
QT_MOC_LITERAL(8, 87, 9), // "zero_slot"
QT_MOC_LITERAL(9, 97, 8), // "one_slot"
QT_MOC_LITERAL(10, 106, 8), // "two_slot"
QT_MOC_LITERAL(11, 115, 10), // "three_slot"
QT_MOC_LITERAL(12, 126, 9), // "four_slot"
QT_MOC_LITERAL(13, 136, 9), // "five_slot"
QT_MOC_LITERAL(14, 146, 8), // "six_slot"
QT_MOC_LITERAL(15, 155, 10), // "seven_slot"
QT_MOC_LITERAL(16, 166, 10), // "eight_slot"
QT_MOC_LITERAL(17, 177, 9), // "nine_slot"
QT_MOC_LITERAL(18, 187, 12), // "decimal_slot"
QT_MOC_LITERAL(19, 200, 9), // "left_slot"
QT_MOC_LITERAL(20, 210, 10) // "right_slot"

    },
    "gui::keyboardWindow\0character_signal\0"
    "\0c\0plus_slot\0minus_slot\0divide_slot\0"
    "multiply_slot\0zero_slot\0one_slot\0"
    "two_slot\0three_slot\0four_slot\0five_slot\0"
    "six_slot\0seven_slot\0eight_slot\0nine_slot\0"
    "decimal_slot\0left_slot\0right_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui__keyboardWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  107,    2, 0x08 /* Private */,
       5,    0,  108,    2, 0x08 /* Private */,
       6,    0,  109,    2, 0x08 /* Private */,
       7,    0,  110,    2, 0x08 /* Private */,
       8,    0,  111,    2, 0x08 /* Private */,
       9,    0,  112,    2, 0x08 /* Private */,
      10,    0,  113,    2, 0x08 /* Private */,
      11,    0,  114,    2, 0x08 /* Private */,
      12,    0,  115,    2, 0x08 /* Private */,
      13,    0,  116,    2, 0x08 /* Private */,
      14,    0,  117,    2, 0x08 /* Private */,
      15,    0,  118,    2, 0x08 /* Private */,
      16,    0,  119,    2, 0x08 /* Private */,
      17,    0,  120,    2, 0x08 /* Private */,
      18,    0,  121,    2, 0x08 /* Private */,
      19,    0,  122,    2, 0x08 /* Private */,
      20,    0,  123,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Char,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gui::keyboardWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<keyboardWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->character_signal((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 1: _t->plus_slot(); break;
        case 2: _t->minus_slot(); break;
        case 3: _t->divide_slot(); break;
        case 4: _t->multiply_slot(); break;
        case 5: _t->zero_slot(); break;
        case 6: _t->one_slot(); break;
        case 7: _t->two_slot(); break;
        case 8: _t->three_slot(); break;
        case 9: _t->four_slot(); break;
        case 10: _t->five_slot(); break;
        case 11: _t->six_slot(); break;
        case 12: _t->seven_slot(); break;
        case 13: _t->eight_slot(); break;
        case 14: _t->nine_slot(); break;
        case 15: _t->decimal_slot(); break;
        case 16: _t->left_slot(); break;
        case 17: _t->right_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (keyboardWindow::*)(char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&keyboardWindow::character_signal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gui::keyboardWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_gui__keyboardWindow.data,
    qt_meta_data_gui__keyboardWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gui::keyboardWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui::keyboardWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gui__keyboardWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gui::keyboardWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void gui::keyboardWindow::character_signal(char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
