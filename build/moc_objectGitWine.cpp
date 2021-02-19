/****************************************************************************
** Meta object code from reading C++ file 'objectGitWine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/obj/objectGitWine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectGitWine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objectGitWine_t {
    QByteArrayData data[8];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_objectGitWine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_objectGitWine_t qt_meta_stringdata_objectGitWine = {
    {
QT_MOC_LITERAL(0, 0, 13), // "objectGitWine"
QT_MOC_LITERAL(1, 14, 20), // "outputPrgressSignals"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 17), // "overThreadSignals"
QT_MOC_LITERAL(4, 54, 18), // "outputPrgressSlots"
QT_MOC_LITERAL(5, 73, 6), // "string"
QT_MOC_LITERAL(6, 80, 4), // "text"
QT_MOC_LITERAL(7, 85, 16) // "curlPrgressSlots"

    },
    "objectGitWine\0outputPrgressSignals\0\0"
    "overThreadSignals\0outputPrgressSlots\0"
    "string\0text\0curlPrgressSlots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objectGitWine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void objectGitWine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<objectGitWine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->outputPrgressSignals(); break;
        case 1: _t->overThreadSignals(); break;
        case 2: _t->outputPrgressSlots((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 3: _t->curlPrgressSlots(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (objectGitWine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectGitWine::outputPrgressSignals)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (objectGitWine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectGitWine::overThreadSignals)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject objectGitWine::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_objectGitWine.data,
    qt_meta_data_objectGitWine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *objectGitWine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objectGitWine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objectGitWine.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int objectGitWine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void objectGitWine::outputPrgressSignals()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void objectGitWine::overThreadSignals()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
