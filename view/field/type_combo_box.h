#ifndef TYPECOMBOBOX_H
#define TYPECOMBOBOX_H

#include <QComboBox>

#include <model/villager/villager_type.h>

class TypeComboBox : public QComboBox {
public:
    TypeComboBox(QWidget* = nullptr);

    const VillagerType* currentType() const;
};

#endif // TYPECOMBOBOX_H