#include "farmer.h"

Farmer::Farmer(const std::string& name, const Gender* gender, const QDate& birthDate, unsigned int crops,
        unsigned int livestock) : Villager(name, gender, birthDate), crops(crops), livestock(livestock) {}

const VillagerType* Farmer::getType() const {
    return &VillagerType::FARMER;
}

unsigned int Farmer::getCrops() const {
    return crops;
}

void Farmer::setCrops(unsigned int crops) {
    this->crops = crops;
}

unsigned int Farmer::getLivestock() const {
    return livestock;
}

void Farmer::setLivestock(unsigned int livestock) {
    this->livestock = livestock;
}

double Farmer::getTaxes() const {
    return Villager::getTaxes() + 0.1 * crops + 4.0 * livestock;
}

bool Farmer::load(const QJsonObject& json) {
    if (!Villager::load(json)) return false;

    if (!json["crops"].isDouble()) return false;
    crops = json["crops"].toInt();

    if (!json["livestock"].isDouble()) return false;
    livestock = json["livestock"].toInt();

    return true;
}

void Farmer::save(QJsonObject& json) const {
    Villager::save(json);

    json["crops"] = static_cast<double>(crops);
    json["livestock"] = static_cast<double>(livestock);
}
