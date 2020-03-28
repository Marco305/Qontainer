TEMPLATE = app
TARGET = Qontainer
QT += core
QT += gui
QT += widgets
QMAKE_CXXFLAGS += -std=c++11
RESOURCES += resources.qrc

SOURCES += main.cpp \
    model/model.cpp \
    model/villager/gender.cpp \
    model/villager/villager_type.cpp \
    model/villager/villager.cpp \
    model/villager/salaried.cpp \
    model/villager/guard.cpp \
	model/villager/armorer.cpp \
    model/villager/farmer.cpp \
    model/villager/alchemist.cpp \
    model/villager/cleric.cpp \
    view/main_window.cpp \
    view/item_widget.cpp \
    view/item_info_widget.cpp \
    view/list_widget.cpp \
    view/search_widget.cpp \
    view/create_edit_dialog.cpp \
    view/filter.cpp \
    view/field/birth_date_search.cpp \
    view/field/comparison_widget.cpp \
    view/field/double_spin_box_search.cpp \
    view/field/spin_box_search.cpp \
    view/field/type_combo_box.cpp

HEADERS += model/container.h \
    model/model.h \
    model/villager/gender.h \
    model/villager/villager_type.h \
    model/villager/villager.h \
    model/villager/salaried.h \
    model/villager/guard.h \
	model/villager/armorer.h \
    model/villager/farmer.h \
    model/villager/alchemist.h \
    model/villager/cleric.h \
    view/main_window.h \
    view/item_widget.h \
    view/item_info_widget.h \
    view/list_widget.h \
    view/search_widget.h \
    view/create_edit_dialog.h \
    view/filter.h \
    view/field/birth_date_search.h \
    view/field/comparison_widget.h \
    view/field/double_spin_box_search.h \
    view/field/gender_buttons.h \
    view/field/operator_util.h \
    view/field/rank_buttons.h \
    view/field/spin_box_search.h \
    view/field/type_combo_box.h