#include "villager_type.h"
#include "guard.h"
#include "armorer.h"
#include "farmer.h"
#include "alchemist.h"
#include "cleric.h"

VillagerType::VillagerType(unsigned int index, const std::string& name, Villager* (*fun)()) : index_(index), name_(name),
    createFunction(fun) {}

bool VillagerType::operator==(const VillagerType& type) const {
    return index_ == type.index_;
}

bool VillagerType::operator!=(const VillagerType& type) const {
    return !(type == *this);
}

unsigned int VillagerType::index() const {
    return index_;
}

std::string VillagerType::name() const {
    return name_;
}

Villager* VillagerType::newInstance() const {
    return createFunction();
}

std::vector<const VillagerType*> VillagerType::vector() {
    return std::vector<const VillagerType*>({&VILLAGER, &GUARD, &ARMORER, &FARMER, &ALCHEMIST, &CLERIC});
}

template <typename T>
Villager* VillagerType::create() {
    return new T();
}

const VillagerType VillagerType::VILLAGER = VillagerType(VillagerTypeEnum::VILLAGER, "Villager", &create<Villager>);
const VillagerType VillagerType::GUARD = VillagerType(VillagerTypeEnum::GUARD, "Guard", &create<Guard>);
const VillagerType VillagerType::ARMORER = VillagerType(VillagerTypeEnum::ARMORER, "Armorer", &create<Armorer>);
const VillagerType VillagerType::FARMER = VillagerType(VillagerTypeEnum::FARMER, "Farmer", &create<Farmer>);
const VillagerType VillagerType::ALCHEMIST = VillagerType(VillagerTypeEnum::ALCHEMIST, "Alchemist", &create<Alchemist>);
const VillagerType VillagerType::CLERIC = VillagerType(VillagerTypeEnum::CLERIC, "Cleric", &create<Cleric>);
