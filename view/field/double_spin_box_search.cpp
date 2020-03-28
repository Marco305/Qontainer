#include <QLayout>

#include "double_spin_box_search.h"

DoubleSpinBoxSearch::DoubleSpinBoxSearch(QWidget* parent) : ComparisonWidget(parent), spinBox(new QDoubleSpinBox()) {
    spinBox->setRange(0.0, 99999999.0);
    layout()->addWidget(spinBox);
}

double DoubleSpinBoxSearch::value() const {
    return spinBox->value();
}
