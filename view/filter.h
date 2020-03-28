#ifndef FILTER_H
#define FILTER_H

#include <QVector>

#include <model/villager/villager.h>
#include <model/villager/guard.h>
#include <view/field/operator_util.h>

class Filter {
private:
    const VillagerType* type;
    QString name;
    QVector<const Gender*> genders;
    QDate birthDate; OperatorUtil::Operator birthDateOp;
    double taxes; OperatorUtil::Operator taxesOp;

    int kills; OperatorUtil::Operator killsOp;
    QVector<const Guard::Rank*> ranks;

    int swords; OperatorUtil::Operator swordsOp;
    int armors; OperatorUtil::Operator armorsOp;

    int crops; OperatorUtil::Operator cropsOp;
    int livestock; OperatorUtil::Operator livestockOp;

    int potions; OperatorUtil::Operator potionsOp;

    double donations; OperatorUtil::Operator donationsOp;

public:
    Filter();

    Filter(const VillagerType*, const QString&, const QVector<const Gender*>&, const QDate&, OperatorUtil::Operator,
            double, OperatorUtil::Operator,
            int, OperatorUtil::Operator, const QVector<const Guard::Rank*>&,
            int, OperatorUtil::Operator, int, OperatorUtil::Operator,
            int, OperatorUtil::Operator, int, OperatorUtil::Operator,
            int, OperatorUtil::Operator,
            double, OperatorUtil::Operator);

    bool accept(const Villager*) const;
};

#endif // FILTER_H