/****************************************************************************
** Meta object code from reading C++ file 'functionWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../gui/functionWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functionWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gui__functionWindow_t {
    QByteArrayData data[14];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui__functionWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui__functionWindow_t qt_meta_stringdata_gui__functionWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "gui::functionWindow"
QT_MOC_LITERAL(1, 20, 7), // "newfunc"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "std::string"
QT_MOC_LITERAL(4, 41, 1), // "f"
QT_MOC_LITERAL(5, 43, 9), // "addToExpr"
QT_MOC_LITERAL(6, 53, 12), // "add_function"
QT_MOC_LITERAL(7, 66, 8), // "addToBox"
QT_MOC_LITERAL(8, 75, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 92, 4), // "item"
QT_MOC_LITERAL(10, 97, 10), // "newfuncadd"
QT_MOC_LITERAL(11, 108, 1), // "b"
QT_MOC_LITERAL(12, 110, 6), // "string"
QT_MOC_LITERAL(13, 117, 1) // "s"

    },
    "gui::functionWindow\0newfunc\0\0std::string\0"
    "f\0addToExpr\0add_function\0addToBox\0"
    "QListWidgetItem*\0item\0newfuncadd\0b\0"
    "string\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui__functionWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
      10,    2,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 12,   11,   13,

       0        // eod
};

void gui::functionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<functionWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newfunc((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->addToExpr((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->add_function(); break;
        case 3: _t->addToBox((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->newfuncadd((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (functionWindow::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&functionWindow::newfunc)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (functionWindow::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&functionWindow::addToExpr)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gui::functionWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_gui__functionWindow.data,
    qt_meta_data_gui__functionWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gui::functionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui::functionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gui__functionWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gui::functionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void gui::functionWindow::newfunc(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gui::functionWindow::addToExpr(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
