#include "villager.h"

double Villager::baseTax = 50.0;

Villager::Villager(const std::string& name, const Gender* gender, const QDate& birthDate)
        : name(name), gender(gender), birthDate(birthDate) {}

const VillagerType* Villager::getType() const {
    return &VillagerType::VILLAGER;
}

std::string Villager::getName() const {
    return name;
}

void Villager::setName(const std::string& name) {
    this->name = name;
}

const Gender* Villager::getGender() const {
    return gender;
}

void Villager::setGender(const Gender* gender) {
    this->gender = gender;
}

QDate Villager::getBirthDate() const {
    return birthDate;
}

void Villager::setBirthDate(const QDate& birthDate) {
    this->birthDate = birthDate;
}

double Villager::getTaxes() const {
    return baseTax;
}

bool Villager::load(const QJsonObject& json) {
    if (!json["name"].isString()) return false;
    name = json["name"].toString().toStdString();

    if (!json["gender"].isDouble()) return false;
    try {
        gender = Gender::vector().at(json["gender"].toInt());
    } catch (std::out_of_range&) { return false; }

    if (!json["birthDate"].isDouble()) return false;
    birthDate = QDate::fromJulianDay(static_cast<long>(json["birthDate"].toDouble()));
    if (!birthDate.isValid()) return false;

    return true;
}

void Villager::save(QJsonObject& json) const {
    json["typeId"] = static_cast<double>(getType()->index());
    json["name"] = QString::fromStdString(name);
    json["gender"] = static_cast<double>(gender->index());
    json["birthDate"] = static_cast<double>(birthDate.toJulianDay());
}

bool Villager::loadFromJson(const QJsonObject& json) {
    return load(json);
}

void Villager::saveToJson(QJsonObject& json) const {
    save(json);
}

bool Villager::operator==(const Villager& villager) const {
    return name == villager.name && gender == villager.gender && birthDate == villager.birthDate;
}

bool Villager::operator!=(const Villager& villager) const {
    return !(villager == *this);
}


double Villager::getBaseTax() {
    return baseTax;
}

void Villager::setBaseTax(double value) {
    baseTax = value;
}

Villager* Villager::createFromJson(const QJsonObject& json) {
    if (json["typeId"].isDouble()) {
        Villager* p;
        try {
            p = VillagerType::vector().at(json["typeId"].toInt())->newInstance();
        } catch (std::out_of_range&) { return nullptr; }
        if (p->loadFromJson(json)) {
            return p;
        }
        delete p;
    }
    return nullptr;
}