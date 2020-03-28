#ifndef SALARIED_H
#define SALARIED_H

#include "villager.h"

class Salaried : public Villager {
public:
    Salaried() = default;

    Salaried(const std::string&, const Gender*, const QDate&);

    virtual double getSalary() const = 0;
};

#endif // SALARIED_H