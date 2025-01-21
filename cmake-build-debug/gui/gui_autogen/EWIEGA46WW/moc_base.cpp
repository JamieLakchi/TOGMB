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
    QByteArrayData data[22];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui__base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui__base_t qt_meta_stringdata_gui__base = {
    {
QT_MOC_LITERAL(0, 0, 9), // "gui::base"
QT_MOC_LITERAL(1, 10, 16), // "function_success"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 1), // "b"
QT_MOC_LITERAL(4, 30, 6), // "string"
QT_MOC_LITERAL(5, 37, 1), // "s"
QT_MOC_LITERAL(6, 39, 16), // "variable_success"
QT_MOC_LITERAL(7, 56, 8), // "evaluate"
QT_MOC_LITERAL(8, 65, 7), // "addChar"
QT_MOC_LITERAL(9, 73, 1), // "c"
QT_MOC_LITERAL(10, 75, 11), // "getKeyboard"
QT_MOC_LITERAL(11, 87, 12), // "getFunctions"
QT_MOC_LITERAL(12, 100, 12), // "getVariables"
QT_MOC_LITERAL(13, 113, 9), // "backspace"
QT_MOC_LITERAL(14, 123, 5), // "reset"
QT_MOC_LITERAL(15, 129, 12), // "add_function"
QT_MOC_LITERAL(16, 142, 11), // "std::string"
QT_MOC_LITERAL(17, 154, 1), // "f"
QT_MOC_LITERAL(18, 156, 9), // "addToExpr"
QT_MOC_LITERAL(19, 166, 11), // "addVariable"
QT_MOC_LITERAL(20, 178, 10), // "dontdothat"
QT_MOC_LITERAL(21, 189, 1) // "q"

    },
    "gui::base\0function_success\0\0b\0string\0"
    "s\0variable_success\0evaluate\0addChar\0"
    "c\0getKeyboard\0getFunctions\0getVariables\0"
    "backspace\0reset\0add_function\0std::string\0"
    "f\0addToExpr\0addVariable\0dontdothat\0q"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui__base[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    2,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   89,    2, 0x08 /* Private */,
       8,    1,   90,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    1,   98,    2, 0x08 /* Private */,
      18,    1,  101,    2, 0x08 /* Private */,
      19,    1,  104,    2, 0x08 /* Private */,
      20,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void gui::base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->function_success((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 1: _t->variable_success((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 2: _t->evaluate(); break;
        case 3: _t->addChar((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 4: _t->getKeyboard(); break;
        case 5: _t->getFunctions(); break;
        case 6: _t->getVariables(); break;
        case 7: _t->backspace(); break;
        case 8: _t->reset(); break;
        case 9: _t->add_function((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 10: _t->addToExpr((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 11: _t->addVariable((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 12: _t->dontdothat((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (base::*)(bool , string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&base::function_success)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (base::*)(bool , string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&base::variable_success)) {
                *result = 1;
                return;
            }
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void gui::base::function_success(bool _t1, string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gui::base::variable_success(bool _t1, string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
