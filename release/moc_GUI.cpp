/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GUI_t {
    QByteArrayData data[15];
    char stringdata[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_t qt_meta_stringdata_GUI = {
    {
QT_MOC_LITERAL(0, 0, 3),
QT_MOC_LITERAL(1, 4, 16),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 14),
QT_MOC_LITERAL(4, 37, 14),
QT_MOC_LITERAL(5, 52, 22),
QT_MOC_LITERAL(6, 75, 24),
QT_MOC_LITERAL(7, 100, 20),
QT_MOC_LITERAL(8, 121, 4),
QT_MOC_LITERAL(9, 126, 21),
QT_MOC_LITERAL(10, 148, 22),
QT_MOC_LITERAL(11, 171, 24),
QT_MOC_LITERAL(12, 196, 10),
QT_MOC_LITERAL(13, 207, 23),
QT_MOC_LITERAL(14, 231, 13)
    },
    "GUI\0crearBaseDeDatos\0\0cambiarModoCMD\0"
    "cambiarModoSQL\0on_botonEnviar_clicked\0"
    "on_limpiarOutput_clicked\0on_input_textChanged\0"
    "arg1\0on_output_textChanged\0"
    "on_input_returnPressed\0on_copyClipboard_clicked\0"
    "vistaArbol\0crearPalabrasReservadas\0"
    "refrescaTabla"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUI *_t = static_cast<GUI *>(_o);
        switch (_id) {
        case 0: _t->crearBaseDeDatos(); break;
        case 1: _t->cambiarModoCMD(); break;
        case 2: _t->cambiarModoSQL(); break;
        case 3: _t->on_botonEnviar_clicked(); break;
        case 4: _t->on_limpiarOutput_clicked(); break;
        case 5: _t->on_input_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_output_textChanged(); break;
        case 7: _t->on_input_returnPressed(); break;
        case 8: _t->on_copyClipboard_clicked(); break;
        case 9: _t->vistaArbol(); break;
        case 10: _t->crearPalabrasReservadas(); break;
        case 11: _t->refrescaTabla(); break;
        default: ;
        }
    }
}

const QMetaObject GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI.data,
      qt_meta_data_GUI,  qt_static_metacall, 0, 0}
};


const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI.stringdata))
        return static_cast<void*>(const_cast< GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
