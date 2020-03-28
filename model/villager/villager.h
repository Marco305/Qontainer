#ifndef VILLAGER_H
#define VILLAGER_H

#include <QJsonObject>
#include <QDate>

#include "gender.h"
#include "villager_type.h"

class Villager {
private:
    std::string name;
    const Gender* gender;
    QDate birthDate;

protected:
    static double baseTax;

    virtual bool load(const QJsonObject&);

    bool loadFromJson(const QJsonObject&);

    virtual void save(QJsonObject&) const;

public:
    Villager() = default;

    Villager(const std::string&, const Gender*, const QDate&);

    virtual ~Villager() = default;

    virtual const VillagerType* getType() const;

    std::string getName() const;
    void setName(const std::string&);

    const Gender* getGender() const;
    void setGender(const Gender*);

    QDate getBirthDate() const;
    void setBirthDate(const QDate&);

    virtual double getTaxes() const;

    void saveToJson(QJsonObject&) const;

    bool operator==(const Villager& rhs) const;

    bool operator!=(const Villager& rhs) const;

    static double getBaseTax();
    static void setBaseTax(double);

    static Villager* createFromJson(const QJsonObject&);
};

#endif // VILLAGER_H