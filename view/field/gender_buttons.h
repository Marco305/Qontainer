#ifndef GENDERBUTTONS_H
#define GENDERBUTTONS_H

#include <QWidget>
#include <QButtonGroup>
#include <QHBoxLayout>

#include <model/villager/gender.h>

template <class T>
class GenderButtons : public QWidget {
private:
    QButtonGroup* group;

public:
    GenderButtons(QWidget* = nullptr);

    QButtonGroup* getGroup() const;

    const Gender* checked() const;

    QVector<const Gender*> checkedMany() const;
};

template <class T>
GenderButtons<T>::GenderButtons(QWidget* parent) : QWidget(parent), group(new QButtonGroup(this)) {
    QHBoxLayout* layout = new QHBoxLayout();
    std::vector<const Gender*> genders = Gender::vector();
    for (unsigned int i = 0; i < genders.size(); ++i) {
        T* button = new T(QString::fromStdString(genders[i]->name()));
        group->addButton(button, i);
        layout->addWidget(button);
    }
    setLayout(layout);
}

template<class T>
QButtonGroup* GenderButtons<T>::getGroup() const {
    return group;
}

template<class T>
const Gender* GenderButtons<T>::checked() const {
    return Gender::vector()[group->checkedId()];
}

template<class T>
QVector<const Gender*> GenderButtons<T>::checkedMany() const {
    QList<QAbstractButton*> buttons = group->buttons();
    std::vector<const Gender*> genders = Gender::vector();
    QVector<const Gender*> vector;
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons.at(i)->isChecked()) {
            vector.push_back(genders[i]);
        }
    }
    return vector;
}

#endif // GENDERBUTTONS_H