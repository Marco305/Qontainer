#include <model/villager/armorer.h>
#include <model/villager/farmer.h>
#include <model/villager/alchemist.h>
#include <model/villager/cleric.h>
#include "filter.h"

Filter::Filter() : type(nullptr), taxes(-1.0), kills(-1), swords(-1), armors(-1), crops(-1), livestock(-1), potions(-1),
        donations(-1.0) {}

Filter::Filter(const VillagerType* type, const QString& name, const QVector<const Gender*>& genders,
        const QDate& birthDate, OperatorUtil::Operator birthDateOp, double taxes, OperatorUtil::Operator taxesOp,
        int kills, OperatorUtil::Operator killsOp, const QVector<const Guard::Rank*>& ranks,
        int swords, OperatorUtil::Operator swordsOp, int armors, OperatorUtil::Operator armorsOp,
        int crops, OperatorUtil::Operator cropsOp, int livestock, OperatorUtil::Operator livestockOp,
        int potions, OperatorUtil::Operator potionsOp,
        double donations, OperatorUtil::Operator donationsOp)
        : type(type), name(name), genders(genders), birthDate(birthDate), birthDateOp(birthDateOp), taxes(taxes), 
        taxesOp(taxesOp),
        kills(kills), killsOp(killsOp), ranks(ranks),
        swords(swords), swordsOp(swordsOp), armors(armors), armorsOp(armorsOp),
        crops(crops), cropsOp(cropsOp), livestock(livestock), livestockOp(livestockOp),
        potions(potions), potionsOp(potionsOp),
        donations(donations), donationsOp(donationsOp) {}

bool Filter::accept(const Villager* item) const {
    return (type == nullptr || item->getType() == type)
        && (name.isEmpty() || QString::fromStdString(item->getName()).contains(name, Qt::CaseInsensitive))
        && (genders.isEmpty() || genders.contains(item->getGender()))
        && (!birthDate.isValid() || OperatorUtil::compare(birthDateOp, item->getBirthDate(), birthDate))
        && (taxes < 0.0 || OperatorUtil::compare(taxesOp, item->getTaxes(), taxes))
        && (kills < 0 || OperatorUtil::compare<int>(killsOp, static_cast<const Guard*>(item)->getKills(), kills))
        && (ranks.isEmpty() || ranks.contains(static_cast<const Guard*>(item)->getRank()))
        && (swords < 0 || OperatorUtil::compare<int>(swordsOp, static_cast<const Armorer*>(item)->getSwords(), swords))
        && (armors < 0 || OperatorUtil::compare<int>(armorsOp, static_cast<const Armorer*>(item)->getArmors(), armors))
        && (crops < 0 || OperatorUtil::compare<int>(cropsOp, static_cast<const Farmer*>(item)->getCrops(), crops))
        && (livestock < 0 || OperatorUtil::compare<int>(livestockOp, static_cast<const Farmer*>(item)->getLivestock(), livestock))
        && (potions < 0 || OperatorUtil::compare<int>(potionsOp, static_cast<const Alchemist*>(item)->getPotions(), potions))
        && (donations < 0 || OperatorUtil::compare(donationsOp, static_cast<const Cleric*>(item)->getDonations(), donations));
}
