/****************************************************************************
** Meta object code from reading C++ file 'vekAppAddMT.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/vekAppAddMT.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vekAppAddMT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vekAppAddMT_t {
    QByteArrayData data[16];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vekAppAddMT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vekAppAddMT_t qt_meta_stringdata_vekAppAddMT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "vekAppAddMT"
QT_MOC_LITERAL(1, 12, 10), // "doneAddApp"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "BaseDockData*"
QT_MOC_LITERAL(4, 38, 12), // "BaseAppData*"
QT_MOC_LITERAL(5, 51, 12), // "toObjectArgs"
QT_MOC_LITERAL(6, 64, 11), // "BaseAppData"
QT_MOC_LITERAL(7, 76, 12), // "_unDiyAppAdd"
QT_MOC_LITERAL(8, 89, 7), // "_upData"
QT_MOC_LITERAL(9, 97, 12), // "BaseDockData"
QT_MOC_LITERAL(10, 110, 14), // "objectTypeView"
QT_MOC_LITERAL(11, 125, 12), // "objectButton"
QT_MOC_LITERAL(12, 138, 9), // "plugsLoad"
QT_MOC_LITERAL(13, 148, 17), // "clicked_rightMenu"
QT_MOC_LITERAL(14, 166, 3), // "pos"
QT_MOC_LITERAL(15, 170, 25) // "onTaskBoxContextMenuEvent"

    },
    "vekAppAddMT\0doneAddApp\0\0BaseDockData*\0"
    "BaseAppData*\0toObjectArgs\0BaseAppData\0"
    "_unDiyAppAdd\0_upData\0BaseDockData\0"
    "objectTypeView\0objectButton\0plugsLoad\0"
    "clicked_rightMenu\0pos\0onTaskBoxContextMenuEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vekAppAddMT[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    0,   62,    2, 0x06 /* Public */,
       8,    3,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   70,    2, 0x08 /* Private */,
      12,    0,   71,    2, 0x08 /* Private */,
      13,    1,   72,    2, 0x08 /* Private */,
      15,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 4, 0x80000000 | 10,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   14,
    QMetaType::Void,

       0        // eod
};

void vekAppAddMT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vekAppAddMT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doneAddApp((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        case 1: _t->toObjectArgs((*reinterpret_cast< BaseAppData(*)>(_a[1]))); break;
        case 2: _t->_unDiyAppAdd(); break;
        case 3: _t->_upData((*reinterpret_cast< BaseDockData(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2])),(*reinterpret_cast< objectTypeView(*)>(_a[3]))); break;
        case 4: _t->objectButton(); break;
        case 5: _t->plugsLoad(); break;
        case 6: _t->clicked_rightMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: _t->onTaskBoxContextMenuEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vekAppAddMT::*)(BaseDockData * , BaseAppData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddMT::doneAddApp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vekAppAddMT::*)(BaseAppData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddMT::toObjectArgs)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (vekAppAddMT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddMT::_unDiyAppAdd)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (vekAppAddMT::*)(BaseDockData , BaseAppData * , objectTypeView );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppAddMT::_upData)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vekAppAddMT::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_vekAppAddMT.data,
    qt_meta_data_vekAppAddMT,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vekAppAddMT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vekAppAddMT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vekAppAddMT.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vekAppAddMT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void vekAppAddMT::doneAddApp(BaseDockData * _t1, BaseAppData * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void vekAppAddMT::toObjectArgs(BaseAppData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void vekAppAddMT::_unDiyAppAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void vekAppAddMT::_upData(BaseDockData _t1, BaseAppData * _t2, objectTypeView _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
