/****************************************************************************
** Meta object code from reading C++ file 'base.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../gui/base.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gui__base_t {
    QByteArrayData data[15];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui__base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui__base_t qt_meta_stringdata_gui__base = {
    {
QT_MOC_LITERAL(0, 0, 9), // "gui::base"
QT_MOC_LITERAL(1, 10, 8), // "evaluate"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "addChar"
QT_MOC_LITERAL(4, 28, 1), // "c"
QT_MOC_LITERAL(5, 30, 11), // "getKeyboard"
QT_MOC_LITERAL(6, 42, 12), // "getFunctions"
QT_MOC_LITERAL(7, 55, 12), // "getVariables"
QT_MOC_LITERAL(8, 68, 9), // "backspace"
QT_MOC_LITERAL(9, 78, 5), // "reset"
QT_MOC_LITERAL(10, 84, 12), // "add_function"
QT_MOC_LITERAL(11, 97, 11), // "std::string"
QT_MOC_LITERAL(12, 109, 1), // "f"
QT_MOC_LITERAL(13, 111, 17), // "addFunctionToExpr"
QT_MOC_LITERAL(14, 129, 11) // "addVariable"

    },
    "gui::base\0evaluate\0\0addChar\0c\0getKeyboard\0"
    "getFunctions\0getVariables\0backspace\0"
    "reset\0add_function\0std::string\0f\0"
    "addFunctionToExpr\0addVariable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui__base[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    1,   65,    2, 0x08 /* Private */,
       5,    0,   68,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      13,    1,   76,    2, 0x08 /* Private */,
      14,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void gui::base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->evaluate(); break;
        case 1: _t->addChar((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 2: _t->getKeyboard(); break;
        case 3: _t->getFunctions(); break;
        case 4: _t->getVariables(); break;
        case 5: _t->backspace(); break;
        case 6: _t->reset(); break;
        case 7: _t->add_function((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->addFunctionToExpr((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 9: _t->addVariable((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gui::base::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_gui__base.data,
    qt_meta_data_gui__base,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gui::base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui::base::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gui__base.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int gui::base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
