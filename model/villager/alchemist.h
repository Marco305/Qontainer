#ifndef ALCHEMIST_H
#define ALCHEMIST_H

#include "villager.h"

class Alchemist : public Villager {
private:
    unsigned int potions;

protected:
    bool load(const QJsonObject&) override;

    void save(QJsonObject&) const override;

public:
    Alchemist() = default;

    Alchemist(const std::string&, const Gender*, const QDate&, unsigned int);

    const VillagerType* getType() const override;

    unsigned int getPotions() const;
    void setPotions(unsigned int);

    double getTaxes() const override;
};

#endif // ALCHEMIST_H