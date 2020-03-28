#include "armorer.h"

Armorer::Armorer(const std::string& name, const Gender* gender, const QDate& birthDate, unsigned int swords,
        unsigned int armors) : Salaried(name, gender, birthDate), swords(swords), armors(armors) {}

const VillagerType* Armorer::getType() const {
    return &VillagerType::ARMORER;
}

unsigned int Armorer::getSwords() const {
    return swords;
}

void Armorer::setSwords(unsigned int swords) {
    this->swords = swords;
}

unsigned int Armorer::getArmors() const {
    return armors;
}

void Armorer::setArmors(unsigned int armors) {
    this->armors = armors;
}

double Armorer::getSalary() const {
    return 1.0 * swords + 2.5 * armors;
}

bool Armorer::load(const QJsonObject& json) {
    if (!Villager::load(json)) return false;

    if (!json["swords"].isDouble()) return false;
    swords = json["swords"].toInt();

    if (!json["armors"].isDouble()) return false;
    armors = json["armors"].toInt();

    return true;
}

void Armorer::save(QJsonObject& json) const {
    Villager::save(json);

    json["swords"] = static_cast<double>(swords);
    json["armors"] = static_cast<double>(armors);
}
