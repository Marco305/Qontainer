#ifndef ARMORER_H
#define ARMORER_H

#include "salaried.h"

class Armorer : public Salaried {
private:
    unsigned int swords;
    unsigned int armors;

protected:
    bool load(const QJsonObject&) override;

    void save(QJsonObject&) const override;

public:
    Armorer() = default;

    Armorer(const std::string&, const Gender*, const QDate&, unsigned int, unsigned int);

    const VillagerType* getType() const override;

    unsigned int getSwords() const;
    void setSwords(unsigned int);

    unsigned int getArmors() const;
    void setArmors(unsigned int);

    double getSalary() const override;
};

#endif // ARMORER_H