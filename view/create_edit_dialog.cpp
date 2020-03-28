#include <model/villager/guard.h>
#include <model/villager/armorer.h>
#include <model/villager/farmer.h>
#include <model/villager/alchemist.h>
#include <model/villager/cleric.h>
#include "create_edit_dialog.h"

CreateEditDialog::CreateEditDialog(QWidget* parent, Villager* item) : QDialog(parent), item(item) {
    setMinimumSize(500, 400);
    setModal(true);
    setWindowTitle(item == nullptr ? "Create Villager" : "Edit Villager");
    setWindowIcon(QIcon(":/icon.png"));

    QVBoxLayout* main = new QVBoxLayout();

    // form
    QFormLayout* form = new QFormLayout();
    form->setVerticalSpacing(20);

    typeField = new TypeComboBox();
    form->addRow("Type:", typeField);
    connect(typeField, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, item, form](int index) {
        if (index < 0) return;

        // clear form
        while (form->rowCount() > 1) {
            form->removeRow(1); // also deletes widgets
        }

        // generate new form
        nameField = new QLineEdit();
        if (item != nullptr) {
            nameField->setText(QString::fromStdString(item->getName()));
        }
        connect(nameField, &QLineEdit::textChanged, this, &CreateEditDialog::completeChanged);
        form->addRow("Name:", nameField);

        genderField = new GenderButtons<QRadioButton>();
        if (item != nullptr) {
            genderField->getGroup()->button(item->getGender()->index())->setChecked(true);
        }
        connect(genderField->getGroup(), QOverload<int>::of(&QButtonGroup::buttonClicked), this,
                &CreateEditDialog::completeChanged);
        form->addRow("Gender:", genderField);

        birthDateField = new QDateEdit();
        if (item != nullptr) {
            birthDateField->setDate(item->getBirthDate());
        }
        connect(birthDateField, &QDateTimeEdit::dateChanged, this, &CreateEditDialog::completeChanged);
        form->addRow("Birth Date:", birthDateField);

        if (index != VillagerTypeEnum::VILLAGER) {
            bool editSameType = item != nullptr && static_cast<unsigned int>(index) == item->getType()->index();
            Villager* v = editSameType ? item : VillagerType::vector()[index]->newInstance(); // dummy ptr for dynamic_cast

            if (Guard* guard = dynamic_cast<Guard*>(v)) {
                killsField = new QSpinBox();
                killsField->setRange(0, 99999999);
                if (editSameType) {
                    killsField->setValue(guard->getKills());
                }
                form->addRow("Kills:", killsField);

                rankField = new RankButtons<QRadioButton>();
                if (editSameType) {
                    rankField->getGroup()->button(guard->getRank()->index())->setChecked(true);
                }
                connect(rankField->getGroup(), QOverload<int>::of(&QButtonGroup::buttonClicked), this,
                        &CreateEditDialog::completeChanged);
                form->addRow("Rank:", rankField);
            } else if (Armorer* armorer = dynamic_cast<Armorer*>(v)) {
                swordsField = new QSpinBox();
                swordsField->setRange(0, 99999999);
                if (editSameType) {
                    swordsField->setValue(armorer->getSwords());
                }
                form->addRow("Swords:", swordsField);

                armorsField = new QSpinBox();
                armorsField->setRange(0, 99999999);
                if (editSameType) {
                    armorsField->setValue(armorer->getArmors());
                }
                form->addRow("Armors:", armorsField);
            } else if (Farmer* farmer = dynamic_cast<Farmer*>(v)) {
                cropsField = new QSpinBox();
                cropsField->setRange(0, 99999999);
                if (editSameType) {
                    cropsField->setValue(farmer->getCrops());
                }
                form->addRow("Crops:", cropsField);

                livestockField = new QSpinBox();
                livestockField->setRange(0, 99999999);
                if (editSameType) {
                    livestockField->setValue(farmer->getLivestock());
                }
                form->addRow("Livestock:", livestockField);
            } else if (Alchemist* alchemist = dynamic_cast<Alchemist*>(v)) {
                potionsField = new QSpinBox();
                potionsField->setRange(0, 99999999);
                if (editSameType) {
                    potionsField->setValue(alchemist->getPotions());
                }
                form->addRow("Potions:", potionsField);
            } else if (Cleric* cleric = dynamic_cast<Cleric*>(v)) {
                donationsField = new QDoubleSpinBox();
                donationsField->setRange(0.0, 99999999.0);
                if (editSameType) {
                    donationsField->setValue(cleric->getDonations());
                }
                form->addRow("Donations:", donationsField);
            }
            // delete dummy ptr
            if (item == nullptr) {
                delete v;
            }
        }
    });
    connect(typeField, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CreateEditDialog::completeChanged);

    // buttons
    QHBoxLayout* buttons = new QHBoxLayout();

    QPushButton* cancelButton = new QPushButton("Cancel");
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);
    buttons->addWidget(cancelButton);

    okButton = new QPushButton("OK");
    okButton->setDefault(true);
    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    buttons->addWidget(okButton);

    main->addLayout(form);
    main->addLayout(buttons);
    setLayout(main);

    typeField->setCurrentIndex(item != nullptr ? item->getType()->index() : -1);
}

bool CreateEditDialog::isComplete() const {
    if (typeField->currentIndex() < 0) return false;
    if (nameField->text().isEmpty()) return false;
    if (genderField->getGroup()->checkedId() < 0) return false;
    if (!birthDateField->date().isValid()) return false;

    if (typeField->currentIndex() == VillagerTypeEnum::GUARD) {
        if (rankField->getGroup()->checkedId() < 0) return false;
    }

    return true;
}

void CreateEditDialog::accept() {
    const VillagerType* type = typeField->currentType();
    bool editSameType = item != nullptr && type == item->getType();
    Villager* v = editSameType ? item : type->newInstance();

    v->setName(nameField->text().toStdString());
    v->setGender(genderField->checked());
    v->setBirthDate(birthDateField->date());

    if (v->getType() != &VillagerType::VILLAGER) {
        if (Guard* guard = dynamic_cast<Guard*>(v)) {
            guard->setKills(killsField->value());
            guard->setRank(rankField->checked());
        } else if (Armorer* armorer = dynamic_cast<Armorer*>(v)) {
            armorer->setSwords(swordsField->value());
            armorer->setArmors(armorsField->value());
        } else if (Farmer* farmer = dynamic_cast<Farmer*>(v)) {
            farmer->setCrops(cropsField->value());
            farmer->setLivestock(livestockField->value());
        } else if (Alchemist* alchemist = dynamic_cast<Alchemist*>(v)) {
            alchemist->setPotions(potionsField->value());
        } else if (Cleric* cleric = dynamic_cast<Cleric*>(v)) {
            cleric->setDonations(donationsField->value());
        }
    }

    if (item == nullptr) {
        emit itemCreated(v);
    } else {
        emit itemEdited(editSameType ? nullptr : item, v);
    }
    QDialog::accept();
}

void CreateEditDialog::completeChanged() {
    okButton->setEnabled(isComplete());
}
