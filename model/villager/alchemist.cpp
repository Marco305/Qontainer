#include "alchemist.h"

Alchemist::Alchemist(const std::string& name, const Gender* gender, const QDate& date, unsigned int potions)
    : Villager(name, gender, date), potions(potions) {}

const VillagerType* Alchemist::getType() const {
    return &VillagerType::ALCHEMIST;
}

unsigned int Alchemist::getPotions() const {
    return potions;
}

void Alchemist::setPotions(unsigned int potions) {
    this->potions = potions;
}

double Alchemist::getTaxes() const {
    return Villager::getTaxes() + 4.5 * potions;
}

bool Alchemist::load(const QJsonObject& json) {
    if (!Villager::load(json)) return false;

    if (!json["potions"].isDouble()) return false;
    potions = json["potions"].toInt();
	
	return true;
}

void Alchemist::save(QJsonObject& json) const {
    Villager::save(json);

    json["potions"] = static_cast<double>(potions);
}
