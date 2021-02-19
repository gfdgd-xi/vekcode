/****************************************************************************
** Meta object code from reading C++ file 'vekAppListView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/view/aview/vekAppListView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vekAppListView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vekAppListView_t {
    QByteArrayData data[19];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vekAppListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vekAppListView_t qt_meta_stringdata_vekAppListView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "vekAppListView"
QT_MOC_LITERAL(1, 15, 16), // "toObjectArgs_ptr"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "BaseAppData*"
QT_MOC_LITERAL(4, 46, 14), // "objectTypeView"
QT_MOC_LITERAL(5, 61, 15), // "toObjectArgs_cl"
QT_MOC_LITERAL(6, 77, 11), // "BaseAppData"
QT_MOC_LITERAL(7, 89, 10), // "_startTray"
QT_MOC_LITERAL(8, 100, 18), // "setUpDelDataSignal"
QT_MOC_LITERAL(9, 119, 13), // "BaseDockData*"
QT_MOC_LITERAL(10, 133, 22), // "setUpGroupTabIcoSignal"
QT_MOC_LITERAL(11, 156, 8), // "moveSlot"
QT_MOC_LITERAL(12, 165, 11), // "setItemSlot"
QT_MOC_LITERAL(13, 177, 8), // "unAppAdd"
QT_MOC_LITERAL(14, 186, 12), // "setUpDelData"
QT_MOC_LITERAL(15, 199, 12), // "BaseDockData"
QT_MOC_LITERAL(16, 212, 12), // "unExportJson"
QT_MOC_LITERAL(17, 225, 10), // "unDebugApp"
QT_MOC_LITERAL(18, 236, 9) // "ObjectRun"

    },
    "vekAppListView\0toObjectArgs_ptr\0\0"
    "BaseAppData*\0objectTypeView\0toObjectArgs_cl\0"
    "BaseAppData\0_startTray\0setUpDelDataSignal\0"
    "BaseDockData*\0setUpGroupTabIcoSignal\0"
    "moveSlot\0setItemSlot\0unAppAdd\0"
    "setUpDelData\0BaseDockData\0unExportJson\0"
    "unDebugApp\0ObjectRun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vekAppListView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    1,   79,    2, 0x06 /* Public */,
       7,    0,   82,    2, 0x06 /* Public */,
       8,    2,   83,    2, 0x06 /* Public */,
      10,    0,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    3,   92,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 3,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 3, 0x80000000 | 4,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vekAppListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vekAppListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toObjectArgs_ptr((*reinterpret_cast< BaseAppData*(*)>(_a[1])),(*reinterpret_cast< objectTypeView(*)>(_a[2]))); break;
        case 1: _t->toObjectArgs_cl((*reinterpret_cast< BaseAppData(*)>(_a[1]))); break;
        case 2: _t->_startTray(); break;
        case 3: _t->setUpDelDataSignal((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        case 4: _t->setUpGroupTabIcoSignal(); break;
        case 5: _t->moveSlot(); break;
        case 6: _t->setItemSlot(); break;
        case 7: _t->unAppAdd(); break;
        case 8: _t->setUpDelData((*reinterpret_cast< BaseDockData(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2])),(*reinterpret_cast< objectTypeView(*)>(_a[3]))); break;
        case 9: _t->unExportJson(); break;
        case 10: _t->unDebugApp(); break;
        case 11: _t->ObjectRun(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vekAppListView::*)(BaseAppData * , objectTypeView );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppListView::toObjectArgs_ptr)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vekAppListView::*)(BaseAppData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppListView::toObjectArgs_cl)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (vekAppListView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppListView::_startTray)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (vekAppListView::*)(BaseDockData * , BaseAppData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppListView::setUpDelDataSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (vekAppListView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppListView::setUpGroupTabIcoSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vekAppListView::staticMetaObject = { {
    QMetaObject::SuperData::link<QListView::staticMetaObject>(),
    qt_meta_stringdata_vekAppListView.data,
    qt_meta_data_vekAppListView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vekAppListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vekAppListView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vekAppListView.stringdata0))
        return static_cast<void*>(this);
    return QListView::qt_metacast(_clname);
}

int vekAppListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void vekAppListView::toObjectArgs_ptr(BaseAppData * _t1, objectTypeView _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void vekAppListView::toObjectArgs_cl(BaseAppData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void vekAppListView::_startTray()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void vekAppListView::setUpDelDataSignal(BaseDockData * _t1, BaseAppData * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void vekAppListView::setUpGroupTabIcoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
