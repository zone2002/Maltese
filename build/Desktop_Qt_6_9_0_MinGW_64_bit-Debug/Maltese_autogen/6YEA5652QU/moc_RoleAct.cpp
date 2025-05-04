/****************************************************************************
** Meta object code from reading C++ file 'RoleAct.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../include/RoleAct.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RoleAct.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN3ActE_t {};
} // unnamed namespace

template <> constexpr inline auto Act::qt_create_metaobjectdata<qt_meta_tag_ZN3ActE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Act",
        "RoleAct",
        "Rolling",
        "RideScooter",
        "RideMaltese",
        "Bickering",
        "MelodySprint"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'RoleAct'
        QtMocHelpers::EnumData<RoleAct>(1, 1, QMC::EnumFlags{}).add({
            {    2, RoleAct::Rolling },
            {    3, RoleAct::RideScooter },
            {    4, RoleAct::RideMaltese },
            {    5, RoleAct::Bickering },
            {    6, RoleAct::MelodySprint },
        }),
    };
    return QtMocHelpers::metaObjectData<void, qt_meta_tag_ZN3ActE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}

static constexpr auto qt_staticMetaObjectContent_ZN3ActE =
    Act::qt_create_metaobjectdata<qt_meta_tag_ZN3ActE_t>();
static constexpr auto qt_staticMetaObjectStaticContent_ZN3ActE =
    qt_staticMetaObjectContent_ZN3ActE.staticData;
static constexpr auto qt_staticMetaObjectRelocatingContent_ZN3ActE =
    qt_staticMetaObjectContent_ZN3ActE.relocatingData;

Q_CONSTINIT const QMetaObject Act::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent_ZN3ActE.stringdata,
    qt_staticMetaObjectStaticContent_ZN3ActE.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent_ZN3ActE.metaTypes,
    nullptr
} };

QT_WARNING_POP
