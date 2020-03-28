#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateEdit>

#include <view/field/type_combo_box.h>
#include <view/field/gender_buttons.h>
#include <view/field/birth_date_search.h>
#include <view/field/spin_box_search.h>
#include <view/field/double_spin_box_search.h>
#include <view/field/rank_buttons.h>
#include "filter.h"

class SearchWidget : public QGroupBox {
    Q_OBJECT
private:
    TypeComboBox* typeField;
    QLineEdit* nameField;
    GenderButtons<QCheckBox>* genderField;
    BirthDateSearch* birthDateField;
    DoubleSpinBoxSearch* taxesField;

    SpinBoxSearch* killsField;
    RankButtons<QCheckBox>* rankField;

    SpinBoxSearch* swordsField;
    SpinBoxSearch* armorsField;

    SpinBoxSearch* cropsField;
    SpinBoxSearch* livestockField;

    SpinBoxSearch* potionsField;

    DoubleSpinBoxSearch* donationsField;

public:
    SearchWidget(QWidget* = nullptr);

signals:
    void applyFilter(const Filter&);

    void removeFiltered();
};

#endif // SEARCHWIDGET_H