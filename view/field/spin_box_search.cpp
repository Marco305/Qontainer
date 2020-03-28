#include <QLayout>

#include "spin_box_search.h"

SpinBoxSearch::SpinBoxSearch(QWidget* parent) : ComparisonWidget(parent), spinBox(new QSpinBox()) {
    spinBox->setRange(0, 99999999);
    layout()->addWidget(spinBox);
}

int SpinBoxSearch::value() const {
    return spinBox->value();
}
