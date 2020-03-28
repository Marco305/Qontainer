#ifndef BIRTHDATESEARCH_H
#define BIRTHDATESEARCH_H

#include <QDateEdit>

#include "comparison_widget.h"

class BirthDateSearch : public ComparisonWidget {
private:
    QDateEdit* dateEdit;

public:
    BirthDateSearch(QWidget* = nullptr);

    QDate date() const;
};

#endif // BIRTHDATESEARCH_H