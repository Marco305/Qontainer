#ifndef CLERIC_H
#define CLERIC_H

#include "villager.h"

class Cleric : public Villager {
private:
    double donations;

protected:
    bool load(const QJsonObject&) override ;

    void save(QJsonObject&) const override ;

public:
    Cleric() = default;

    Cleric(const std::string, const Gender*, const QDate&, double);

    const VillagerType* getType() const override;

    double getDonations() const;
    void setDonations(double);

    double getTaxes() const override;
};

#endif // CLERIC_H