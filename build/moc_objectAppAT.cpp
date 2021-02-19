/****************************************************************************
** Meta object code from reading C++ file 'objectAppAT.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/obj/objectAppAT.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectAppAT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objectAppAT_t {
    QByteArrayData data[10];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_objectAppAT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_objectAppAT_t qt_meta_stringdata_objectAppAT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "objectAppAT"
QT_MOC_LITERAL(1, 12, 4), // "Tips"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "TipsStr"
QT_MOC_LITERAL(4, 26, 5), // "Error"
QT_MOC_LITERAL(5, 32, 9), // "ErrorInfo"
QT_MOC_LITERAL(6, 42, 6), // "cState"
QT_MOC_LITERAL(7, 49, 4), // "Done"
QT_MOC_LITERAL(8, 54, 13), // "BaseDockData*"
QT_MOC_LITERAL(9, 68, 12) // "BaseAppData*"

    },
    "objectAppAT\0Tips\0\0TipsStr\0Error\0"
    "ErrorInfo\0cState\0Done\0BaseDockData*\0"
    "BaseAppData*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objectAppAT[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    2,   32,    2, 0x06 /* Public */,
       7,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 9,    2,    2,

       0        // eod
};

void objectAppAT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<objectAppAT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Tips((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->Done((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (objectAppAT::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectAppAT::Tips)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (objectAppAT::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectAppAT::Error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (objectAppAT::*)(BaseDockData * , BaseAppData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectAppAT::Done)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject objectAppAT::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_objectAppAT.data,
    qt_meta_data_objectAppAT,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *objectAppAT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objectAppAT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objectAppAT.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int objectAppAT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void objectAppAT::Tips(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void objectAppAT::Error(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void objectAppAT::Done(BaseDockData * _t1, BaseAppData * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
