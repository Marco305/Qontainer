#include "type_combo_box.h"

TypeComboBox::TypeComboBox(QWidget* parent) : QComboBox(parent) {
    std::vector<const VillagerType*> types = VillagerType::vector();
    for (unsigned int i = 0; i < types.size(); ++i) {
        addItem(QString::fromStdString(types[i]->name()));
    }
}

const VillagerType* TypeComboBox::currentType() const {
    try {
        return VillagerType::vector().at(currentIndex());
    } catch (std::out_of_range&) { return nullptr; }
}
