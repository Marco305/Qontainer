#include <QLayout>

#include "birth_date_search.h"

BirthDateSearch::BirthDateSearch(QWidget* parent) : ComparisonWidget(parent), dateEdit(new QDateEdit()) {
    layout()->addWidget(dateEdit);
}

QDate BirthDateSearch::date() const {
    return dateEdit->date();
}
