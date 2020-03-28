#ifndef DOUBLESPINBOXSEARCH_H
#define DOUBLESPINBOXSEARCH_H

#include <QDoubleSpinBox>

#include "comparison_widget.h"

class DoubleSpinBoxSearch : public ComparisonWidget {
private:
    QDoubleSpinBox* spinBox;

public:
    DoubleSpinBoxSearch(QWidget* = nullptr);

    double value() const;
};

#endif // DOUBLESPINBOXSEARCH_H