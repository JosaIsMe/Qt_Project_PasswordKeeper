/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onTrayIconActivated",
        "",
        "QSystemTrayIcon::ActivationReason",
        "reason",
        "onShowMainWindow",
        "on_Login_PushButton_clicked",
        "on_Login_RegisterCheckBox_checkStateChanged",
        "Qt::CheckState",
        "arg1",
        "on_listWidget_doubleClicked",
        "QModelIndex",
        "index",
        "on_ToFiles_clicked",
        "on_ToPasswordGenerators_clicked",
        "on_ToPasswords_clicked",
        "on_ToTexts_clicked",
        "on_PM_SearchButton_clicked",
        "on_PM_AddButton_clicked",
        "on_PM_UpdateButton_clicked",
        "on_PM_RemoveButton_clicked",
        "on_FE_EncryptionButton_clicked",
        "on_FE_DecryptionButton_clicked",
        "on_PG_GenerateButton_clicked",
        "on_PG_CheckBoxUpperCase_checkStateChanged",
        "on_PG_CheckBoxLowerCase_checkStateChanged",
        "on_PG_CheckBoxNumbers_checkStateChanged",
        "on_PG_CheckBoxSymbols_checkStateChanged",
        "on_TE_EncryptionButton_clicked",
        "on_TE_DecryptionButton_clicked",
        "on_Menu_ChangeVaultFilePath_triggered",
        "on_Menu_ChangePassword_triggered",
        "on_actionLog_Out_triggered",
        "on_actionGenerator_triggered",
        "on_actionPasswords_triggered",
        "on_actionTexts_triggered",
        "on_actionFiles_triggered",
        "on_actionChange_File_Path_triggered",
        "on_actionSwitch_to_table_assistant_triggered",
        "on_actionMinimize_to_Tray_triggered",
        "on_PM_SaveAsFileButton_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onTrayIconActivated'
        QtMocHelpers::SlotData<void(QSystemTrayIcon::ActivationReason)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'onShowMainWindow'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Login_PushButton_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Login_RegisterCheckBox_checkStateChanged'
        QtMocHelpers::SlotData<void(const Qt::CheckState &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_listWidget_doubleClicked'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'on_ToFiles_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ToPasswordGenerators_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ToPasswords_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ToTexts_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PM_SearchButton_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PM_AddButton_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PM_UpdateButton_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PM_RemoveButton_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_FE_EncryptionButton_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_FE_DecryptionButton_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PG_GenerateButton_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PG_CheckBoxUpperCase_checkStateChanged'
        QtMocHelpers::SlotData<void(const Qt::CheckState &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_PG_CheckBoxLowerCase_checkStateChanged'
        QtMocHelpers::SlotData<void(const Qt::CheckState &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_PG_CheckBoxNumbers_checkStateChanged'
        QtMocHelpers::SlotData<void(const Qt::CheckState &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_PG_CheckBoxSymbols_checkStateChanged'
        QtMocHelpers::SlotData<void(const Qt::CheckState &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_TE_EncryptionButton_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_TE_DecryptionButton_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Menu_ChangeVaultFilePath_triggered'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Menu_ChangePassword_triggered'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionLog_Out_triggered'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionGenerator_triggered'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionPasswords_triggered'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionTexts_triggered'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionFiles_triggered'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionChange_File_Path_triggered'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionSwitch_to_table_assistant_triggered'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionMinimize_to_Tray_triggered'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PM_SaveAsFileButton_clicked'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onTrayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 1: _t->onShowMainWindow(); break;
        case 2: _t->on_Login_PushButton_clicked(); break;
        case 3: _t->on_Login_RegisterCheckBox_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 4: _t->on_listWidget_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 5: _t->on_ToFiles_clicked(); break;
        case 6: _t->on_ToPasswordGenerators_clicked(); break;
        case 7: _t->on_ToPasswords_clicked(); break;
        case 8: _t->on_ToTexts_clicked(); break;
        case 9: _t->on_PM_SearchButton_clicked(); break;
        case 10: _t->on_PM_AddButton_clicked(); break;
        case 11: _t->on_PM_UpdateButton_clicked(); break;
        case 12: _t->on_PM_RemoveButton_clicked(); break;
        case 13: _t->on_FE_EncryptionButton_clicked(); break;
        case 14: _t->on_FE_DecryptionButton_clicked(); break;
        case 15: _t->on_PG_GenerateButton_clicked(); break;
        case 16: _t->on_PG_CheckBoxUpperCase_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 17: _t->on_PG_CheckBoxLowerCase_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 18: _t->on_PG_CheckBoxNumbers_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 19: _t->on_PG_CheckBoxSymbols_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 20: _t->on_TE_EncryptionButton_clicked(); break;
        case 21: _t->on_TE_DecryptionButton_clicked(); break;
        case 22: _t->on_Menu_ChangeVaultFilePath_triggered(); break;
        case 23: _t->on_Menu_ChangePassword_triggered(); break;
        case 24: _t->on_actionLog_Out_triggered(); break;
        case 25: _t->on_actionGenerator_triggered(); break;
        case 26: _t->on_actionPasswords_triggered(); break;
        case 27: _t->on_actionTexts_triggered(); break;
        case 28: _t->on_actionFiles_triggered(); break;
        case 29: _t->on_actionChange_File_Path_triggered(); break;
        case 30: _t->on_actionSwitch_to_table_assistant_triggered(); break;
        case 31: _t->on_actionMinimize_to_Tray_triggered(); break;
        case 32: _t->on_PM_SaveAsFileButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 33;
    }
    return _id;
}
QT_WARNING_POP
