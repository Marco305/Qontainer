#ifndef FARMER_H
#define FARMER_H

#include "villager.h"

class Farmer : public Villager {
private:
    unsigned int crops;
    unsigned int livestock;

protected:
    bool load(const QJsonObject&) override;

    void save(QJsonObject&) const override ;

public:
    Farmer() = default;

    Farmer(const std::string&, const Gender*, const QDate&, unsigned int, unsigned int);

    const VillagerType* getType() const override;

    unsigned int getCrops() const;
    void setCrops(unsigned int);

    unsigned int getLivestock() const;
    void setLivestock(unsigned int);

    double getTaxes() const override;
};

#endif // FARMER_H