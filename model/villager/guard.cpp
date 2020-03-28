#include "guard.h"

Guard::Rank::Rank(unsigned int index, const std::string& name) : index_(index), name_(name) {}

bool Guard::Rank::operator==(const Guard::Rank& level) const {
    return index_ == level.index_;
}

bool Guard::Rank::operator!=(const Guard::Rank& level) const {
    return !(level == *this);
}

unsigned int Guard::Rank::index() const {
    return index_;
}

std::string Guard::Rank::name() const {
    return name_;
}

std::vector<const Guard::Rank*> Guard::Rank::vector() {
    return std::vector<const Guard::Rank*>({&RECRUIT, &EXPERIENCED, &VETERAN});
}

const Guard::Rank Guard::Rank::RECRUIT = Guard::Rank(Guard::RankEnum::RECRUIT, "Recruit");
const Guard::Rank Guard::Rank::EXPERIENCED = Guard::Rank(Guard::RankEnum::EXPERIENCED, "Experienced");
const Guard::Rank Guard::Rank::VETERAN = Guard::Rank(Guard::RankEnum::VETERAN, "Veteran");

Guard::Guard(const std::string& name, const Gender* gender, const QDate& birthDate, unsigned int kills,
        const Guard::Rank* level) : Salaried(name, gender, birthDate), kills(kills), rank(level) {}

const VillagerType* Guard::getType() const {
    return &VillagerType::GUARD;
}

unsigned int Guard::getKills() const {
    return kills;
}

void Guard::setKills(unsigned int kills) {
    this->kills = kills;
}

const Guard::Rank* Guard::getRank() const {
    return rank;
}

void Guard::setRank(const Guard::Rank* rank) {
    this->rank = rank;
}

double Guard::getSalary() const {
    double base = 0.0;
    switch (rank->index()) {
        case RECRUIT:
            base = 40.0; break;
        case EXPERIENCED:
            base = 60.0; break;
        case VETERAN:
            base = 100.0; break;
    }
    return 3.5 * kills + base;
}

bool Guard::load(const QJsonObject& json) {
    if (!Villager::load(json)) return false;

    if (!json["kills"].isDouble()) return false;
    kills = json["kills"].toInt();

    if(!json["rank"].isDouble()) return false;
    try {
        rank = Rank::vector().at(json["rank"].toInt());
    } catch (std::out_of_range&) { return false; }

    return true;
}

void Guard::save(QJsonObject& json) const {
    Villager::save(json);

    json["kills"] = static_cast<double>(kills);
    json["rank"] = static_cast<double>(rank->index());
}
