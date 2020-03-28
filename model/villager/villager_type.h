#ifndef VILLAGERTYPE_H
#define VILLAGERTYPE_H

#include <unordered_map>
#include <string>
#include <vector>

class Villager;

class VillagerType {
private:
    const unsigned int index_;
    const std::string name_;
    Villager* (* const createFunction)();

    VillagerType(unsigned int, const std::string&, Villager* (*)());

    template <class T>
    static Villager* create();

public:
    bool operator==(const VillagerType&) const;

    bool operator!=(const VillagerType&) const;

    unsigned int index() const;

    std::string name() const;

    Villager* newInstance() const;

    static std::vector<const VillagerType*> vector();

    static const VillagerType VILLAGER, GUARD, ARMORER, FARMER, ALCHEMIST, CLERIC;
};

enum VillagerTypeEnum {VILLAGER, GUARD, ARMORER, FARMER, ALCHEMIST, CLERIC};

#endif // VILLAGERTYPE_H