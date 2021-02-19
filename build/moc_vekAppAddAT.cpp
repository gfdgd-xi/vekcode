/****************************************************************************
** Meta object code from reading C++ file 'vekAppAddAT.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/vekAppAddAT.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vekAppAddAT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vekAppAddAT_t {
    QByteArrayData data[12];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vekAppAddAT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vekAppAddAT_t qt_meta_stringdata_vekAppAddAT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "vekAppAddAT"
QT_MOC_LITERAL(1, 12, 11), // "_unAutoDock"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "autoObjDock"
QT_MOC_LITERAL(4, 37, 13), // "BaseDockData*"
QT_MOC_LITERAL(5, 51, 12), // "BaseAppData*"
QT_MOC_LITERAL(6, 64, 7), // "TipText"
QT_MOC_LITERAL(7, 72, 7), // "TipInfo"
QT_MOC_LITERAL(8, 80, 9), // "ErrorText"
QT_MOC_LITERAL(9, 90, 9), // "ErrorInfo"
QT_MOC_LITERAL(10, 100, 6), // "cState"
QT_MOC_LITERAL(11, 107, 7) // "ObjDone"

    },
    "vekAppAddAT\0_unAutoDock\0\0autoObjDock\0"
    "BaseDockData*\0BaseAppData*\0TipText\0"
    "TipInfo\0ErrorText\0ErrorInfo\0cState\0"
    "ObjDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vekAppAddAT[] = {

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
       1,    0,   39,    2, 0x06 /* Public */,
       3,    2,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x08 /* Private */,
       8,    2,   48,    2, 0x08 /* Private */,
      11,    2,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    9,   10,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,

       0        // eod
};

void vekAppAddAT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vekAppAddAT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_unAutoDock(); break;
        case 1: _t->autoObjDock((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        case 2: _t->TipText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ErrorText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->ObjDone((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vekAppAddAT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddAT::_unAutoDock)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vekAppAddAT::*)(BaseDockData * , BaseAppData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddAT::autoObjDock)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vekAppAddAT::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_vekAppAddAT.data,
    qt_meta_data_vekAppAddAT,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vekAppAddAT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vekAppAddAT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vekAppAddAT.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vekAppAddAT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void vekAppAddAT::_unAutoDock()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void vekAppAddAT::autoObjDock(BaseDockData * _t1, BaseAppData * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
