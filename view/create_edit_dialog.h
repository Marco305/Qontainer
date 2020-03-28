#ifndef CREATEEDITDIALOG_H
#define CREATEEDITDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QRadioButton>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

#include <model/villager/villager.h>
#include <view/field/type_combo_box.h>
#include <view/field/gender_buttons.h>
#include <view/field/rank_buttons.h>

class CreateEditDialog : public QDialog {
    Q_OBJECT
private:
    Villager* item;

    TypeComboBox* typeField;
    QLineEdit* nameField;
    GenderButtons<QRadioButton>* genderField;
    QDateEdit* birthDateField;

    QSpinBox* killsField;
    RankButtons<QRadioButton>* rankField;

    QSpinBox* swordsField;
    QSpinBox* armorsField;

    QSpinBox* cropsField;
    QSpinBox* livestockField;

    QSpinBox* potionsField;

    QDoubleSpinBox* donationsField;

    QPushButton* okButton;

    bool isComplete() const;

    void accept() override;

public:
    CreateEditDialog(QWidget* = nullptr, Villager* = nullptr);

public slots:
    void completeChanged();

signals:
    void itemCreated(Villager*);

    void itemEdited(Villager*, Villager*);
};

#endif // CREATEEDITDIALOG_H