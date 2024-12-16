/****************************************************************************
** Meta object code from reading C++ file 'productwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../productwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'productwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSProductWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSProductWindowENDCLASS = QtMocHelpers::stringData(
    "ProductWindow",
    "handleUpdate",
    "",
    "row",
    "handleDelete",
    "handleAdd",
    "handleSearch",
    "searchText",
    "handleShowAll",
    "saveProductsToFile",
    "loadProductsFromFile",
    "reconnectButtons"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSProductWindowENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[14];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[13];
    char stringdata5[10];
    char stringdata6[13];
    char stringdata7[11];
    char stringdata8[14];
    char stringdata9[19];
    char stringdata10[21];
    char stringdata11[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSProductWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSProductWindowENDCLASS_t qt_meta_stringdata_CLASSProductWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "ProductWindow"
        QT_MOC_LITERAL(14, 12),  // "handleUpdate"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 3),  // "row"
        QT_MOC_LITERAL(32, 12),  // "handleDelete"
        QT_MOC_LITERAL(45, 9),  // "handleAdd"
        QT_MOC_LITERAL(55, 12),  // "handleSearch"
        QT_MOC_LITERAL(68, 10),  // "searchText"
        QT_MOC_LITERAL(79, 13),  // "handleShowAll"
        QT_MOC_LITERAL(93, 18),  // "saveProductsToFile"
        QT_MOC_LITERAL(112, 20),  // "loadProductsFromFile"
        QT_MOC_LITERAL(133, 16)   // "reconnectButtons"
    },
    "ProductWindow",
    "handleUpdate",
    "",
    "row",
    "handleDelete",
    "handleAdd",
    "handleSearch",
    "searchText",
    "handleShowAll",
    "saveProductsToFile",
    "loadProductsFromFile",
    "reconnectButtons"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProductWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x08,    1 /* Private */,
       4,    1,   65,    2, 0x08,    3 /* Private */,
       5,    0,   68,    2, 0x08,    5 /* Private */,
       6,    1,   69,    2, 0x08,    6 /* Private */,
       8,    0,   72,    2, 0x08,    8 /* Private */,
       9,    0,   73,    2, 0x08,    9 /* Private */,
      10,    0,   74,    2, 0x08,   10 /* Private */,
      11,    0,   75,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProductWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSProductWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProductWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProductWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProductWindow, std::true_type>,
        // method 'handleUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleDelete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleShowAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveProductsToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadProductsFromFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reconnectButtons'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ProductWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProductWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->handleDelete((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->handleAdd(); break;
        case 3: _t->handleSearch((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->handleShowAll(); break;
        case 5: _t->saveProductsToFile(); break;
        case 6: _t->loadProductsFromFile(); break;
        case 7: _t->reconnectButtons(); break;
        default: ;
        }
    }
}

const QMetaObject *ProductWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProductWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProductWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProductWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
