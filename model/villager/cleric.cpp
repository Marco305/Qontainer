#include "cleric.h"

Cleric::Cleric(const std::string name, const Gender* gender, const QDate& birthDate, double donations) :
    Villager(name, gender, birthDate), donations(donations) {}

const VillagerType* Cleric::getType() const {
    return &VillagerType::CLERIC;
}

double Cleric::getDonations() const {
    return donations;
}

void Cleric::setDonations(double donations) {
    this->donations = donations;
}

double Cleric::getTaxes() const {
    return 0.05 * donations;
}

bool Cleric::load(const QJsonObject& json) {
    if (!Villager::load(json)) return false;

    if (!json["donations"].isDouble()) return false;
    donations = json["donations"].toDouble();

    return true;
}

void Cleric::save(QJsonObject& json) const {
    Villager::save(json);

    json["donations"] = donations;
}
