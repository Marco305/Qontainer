#ifndef RANKBUTTONS_H
#define RANKBUTTONS_H

#include <QWidget>
#include <QButtonGroup>
#include <QHBoxLayout>

#include <model/villager/guard.h>

template <class T>
class RankButtons : public QWidget {
private:
    QButtonGroup* group;

public:
    RankButtons(QWidget* = nullptr);

    QButtonGroup* getGroup() const;

    const Guard::Rank* checked() const;

    QVector<const Guard::Rank*> checkedMany() const;
};

template <class T>
RankButtons<T>::RankButtons(QWidget* parent) : QWidget(parent), group(new QButtonGroup(this)) {
    QHBoxLayout* layout = new QHBoxLayout();
    std::vector<const Guard::Rank*> ranks = Guard::Rank::vector();
    for (unsigned int i = 0; i < ranks.size(); ++i) {
        T* button = new T(QString::fromStdString(ranks[i]->name()));
        group->addButton(button, i);
        layout->addWidget(button);
    }
    setLayout(layout);
}

template<class T>
QButtonGroup* RankButtons<T>::getGroup() const {
    return group;
}

template<class T>
const Guard::Rank* RankButtons<T>::checked() const {
    return Guard::Rank::vector()[group->checkedId()];
}

template<class T>
QVector<const Guard::Rank*> RankButtons<T>::checkedMany() const {
    QList<QAbstractButton*> buttons = group->buttons();
    std::vector<const Guard::Rank*> ranks = Guard::Rank::vector();
    QVector<const Guard::Rank*> vector;
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons.at(i)->isChecked()) {
            vector.push_back(ranks[i]);
        }
    }
    return vector;
}

#endif // RANKBUTTONS_H