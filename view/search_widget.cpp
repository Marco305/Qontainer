#include <QFormLayout>
#include <QPushButton>

#include <model/villager/guard.h>
#include <model/villager/armorer.h>
#include <model/villager/farmer.h>
#include <model/villager/alchemist.h>
#include <model/villager/cleric.h>
#include "search_widget.h"

SearchWidget::SearchWidget(QWidget* parent) : QGroupBox("Filter", parent) {
    QVBoxLayout* main = new QVBoxLayout();

    // form
    QFormLayout* form = new QFormLayout();
    form->setVerticalSpacing(20);

    typeField = new TypeComboBox();
    typeField->addItem("<empty>");
    typeField->setCurrentIndex(typeField->count() - 1);
    form->addRow("Type:", typeField);

    nameField = new QLineEdit();
    form->addRow("Name:", nameField);

    genderField = new GenderButtons<QCheckBox>();
    genderField->getGroup()->setExclusive(false);
    form->addRow("Gender:", genderField);

    birthDateField = new BirthDateSearch();
    form->addRow("Birth Date:", birthDateField);

    taxesField = new DoubleSpinBoxSearch();
    form->addRow("Taxes:", taxesField);

    connect(typeField, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, form](int index) {
        // clear form
        while (form->rowCount() > 5) {
            form->removeRow(5); // also deletes widgets
        }

        if (index == typeField->count() - 1) return; // empty

        // generate new form
        if (index != VillagerTypeEnum::VILLAGER) {
            Villager* v = VillagerType::vector()[index]->newInstance(); // dummy ptr for dynamic_cast

            if (dynamic_cast<Guard*>(v)) {
                killsField = new SpinBoxSearch();
                form->addRow("Kills:", killsField);

                rankField = new RankButtons<QCheckBox>();
                rankField->getGroup()->setExclusive(false);
                form->addRow("Rank:", rankField);
            } else if (dynamic_cast<Armorer*>(v)) {
                swordsField = new SpinBoxSearch();
                form->addRow("Swords:", swordsField);

                armorsField = new SpinBoxSearch();
                form->addRow("Armors:", armorsField);
            } else if (dynamic_cast<Farmer*>(v)) {
                cropsField = new SpinBoxSearch();
                form->addRow("Crops:", cropsField);

                livestockField = new SpinBoxSearch();
                form->addRow("Livestock:", livestockField);
            } else if (dynamic_cast<Alchemist*>(v)) {
                potionsField = new SpinBoxSearch();
                form->addRow("Potions:", potionsField);
            } else if (dynamic_cast<Cleric*>(v)) {
                donationsField = new DoubleSpinBoxSearch();
                form->addRow("Donations:", donationsField);
            }
            // delete dummy ptr
            delete v;
        }

    });

    // buttons
    QHBoxLayout* buttons = new QHBoxLayout();

    QPushButton* clearButton = new QPushButton("Clear");
    connect(clearButton, &QAbstractButton::clicked, this, [this]() {
        emit applyFilter(Filter());
    });
    buttons->addWidget(clearButton);

    QPushButton* searchButton = new QPushButton("Search");
    connect(searchButton, &QAbstractButton::clicked, this, [this]() {
        int type = typeField->currentIndex();
        emit applyFilter(Filter(typeField->currentType(), nameField->text(), genderField->checkedMany(),
                birthDateField->date(), birthDateField->currentOperator(), taxesField->value(),
                taxesField->currentOperator(),
                type == VillagerTypeEnum::GUARD ? killsField->value() : -1,
                type == VillagerTypeEnum::GUARD ? killsField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::GUARD ? rankField->checkedMany() : QVector<const Guard::Rank*>(),
                type == VillagerTypeEnum::ARMORER ? armorsField->value() : -1,
                type == VillagerTypeEnum::ARMORER ? armorsField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::ARMORER ? swordsField->value() : -1,
                type == VillagerTypeEnum::ARMORER ? swordsField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::FARMER ? cropsField->value() : -1,
                type == VillagerTypeEnum::FARMER ? cropsField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::FARMER ? livestockField->value() : -1,
                type == VillagerTypeEnum::FARMER ? livestockField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::ALCHEMIST ? potionsField->value() : -1,
                type == VillagerTypeEnum::ALCHEMIST ? potionsField->currentOperator() : OperatorUtil::Operator::UNDEFINED,
                type == VillagerTypeEnum::CLERIC ? donationsField->value() : -1.0,
                type == VillagerTypeEnum::CLERIC ? donationsField->currentOperator() : OperatorUtil::Operator::UNDEFINED));
    });
    buttons->addWidget(searchButton);

    QPushButton* removeButton = new QPushButton("Remove");
    connect(removeButton, &QAbstractButton::clicked, this, &SearchWidget::removeFiltered);
    buttons->addWidget(removeButton);

    main->addLayout(form);
    main->addLayout(buttons);
    setLayout(main);
}
