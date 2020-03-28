#ifndef GUARD_H
#define GUARD_H

#include "salaried.h"

class Guard : public Salaried {
public:
    class Rank {
    private:
        const unsigned int index_;
        const std::string name_;

        Rank(unsigned int, const std::string&);

    public:
        Rank() = default;

        bool operator==(const Rank&) const;

        bool operator!=(const Rank&) const;

        unsigned int index() const;

        std::string name() const;

        static std::vector<const Rank*> vector();

        static const Rank RECRUIT, EXPERIENCED, VETERAN;
    };

    enum RankEnum {RECRUIT, EXPERIENCED, VETERAN};

private:
    unsigned int kills;
    const Rank* rank;

protected:
    bool load(const QJsonObject&) override;

    void save(QJsonObject&) const override;

public:
    Guard() = default;

    Guard(const std::string&, const Gender*, const QDate&, unsigned int, const Rank*);

    const VillagerType* getType() const override;

    unsigned int getKills() const;
    void setKills(unsigned int);

    const Rank* getRank() const;
    void setRank(const Rank*);

    double getSalary() const override;
};

#endif // GUARD_H