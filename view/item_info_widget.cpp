#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <model/villager/salaried.h>
#include <model/villager/guard.h>
#include <model/villager/armorer.h>
#include <model/villager/farmer.h>
#include <model/villager/alchemist.h>
#include <model/villager/cleric.h>
#include "item_info_widget.h"
#include "create_edit_dialog.h"

ItemInfoWidget::ItemInfoWidget(QWidget* parent) : QWidget(parent), layout(new QVBoxLayout()) {
    setLayout(layout);
}

void ItemInfoWidget::update(Villager* item) {
    clearWidgets(layout);

    if (item == nullptr) return;

    // info
    QFormLayout* info = new QFormLayout();
    info->setHorizontalSpacing(30);
    info->setVerticalSpacing(20);

    QLabel* typeLabel = new QLabel(QString::fromStdString(item->getType()->name()));
    QFont font = typeLabel->font();
    font.setBold(true);
    typeLabel->setFont(font);
    info->addWidget(typeLabel);

    info->addRow("Name:", new QLabel(QString::fromStdString(item->getName())));
    info->addRow("Gender:", new QLabel(QString::fromStdString(item->getGender()->name())));
    info->addRow("Birth Date:", new QLabel(item->getBirthDate().toString("dd/MM/yyyy")));
    info->addRow("Taxes:", new QLabel(QString::number(item->getTaxes())));

    if (item->getType() != &VillagerType::VILLAGER) {
        if (Salaried* salaried = dynamic_cast<Salaried*>(item)) {
            info->addRow("Salary:", new QLabel(QString::number(salaried->getSalary())));

            if (Guard* guard = dynamic_cast<Guard*>(salaried)) {
                info->addRow("Kills:", new QLabel(QString::number(guard->getKills())));
                info->addRow("Rank:", new QLabel(QString::fromStdString(guard->getRank()->name())));
            }
            else if (Armorer* armorer = dynamic_cast<Armorer*>(salaried)) {
                info->addRow("Swords:", new QLabel(QString::number(armorer->getSwords())));
                info->addRow("Armors:", new QLabel(QString::number(armorer->getArmors())));
            }
        }
        else if (Farmer* farmer = dynamic_cast<Farmer*>(item)) {
            info->addRow("Crops:", new QLabel(QString::number(farmer->getCrops())));
            info->addRow("Livestock:", new QLabel(QString::number(farmer->getLivestock())));
        }
        else if (Alchemist* alchemist = dynamic_cast<Alchemist*>(item)) {
            info->addRow("Potions:", new QLabel(QString::number(alchemist->getPotions())));
        }
        else if (Cleric* cleric = dynamic_cast<Cleric*>(item)) {
            info->addRow("Donations:", new QLabel(QString::number(cleric->getDonations())));
        }
    }

    // buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* editButton = new QPushButton("Edit");
    connect(editButton, &QAbstractButton::clicked, this, [this, item]() {
        CreateEditDialog* dialog = new CreateEditDialog(this, item);
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        connect(dialog, &CreateEditDialog::itemEdited, this, [this](Villager* oldItem, Villager* newItem) {
            emit itemEdited(oldItem, newItem);
        });
        dialog->show();
    });
    buttonsLayout->addWidget(editButton);

    QPushButton* removeButton = new QPushButton("Remove");
    connect(removeButton, &QAbstractButton::clicked, this, [this, item]() {
        emit itemDeleted(item);
    });
    buttonsLayout->addWidget(removeButton);

    layout->addLayout(info, 9);
    layout->addLayout(buttonsLayout, 1);
}

void ItemInfoWidget::clearWidgets(QLayout* layout) {
    if (layout != nullptr) {
        while (layout->count() > 0) {
            QLayoutItem *item = layout->takeAt(0);
            delete item->widget();
            clearWidgets(item->layout());
            delete item;
        }
    }
}
