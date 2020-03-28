#ifndef SPINBOXSEARCH_H
#define SPINBOXSEARCH_H

#include <QSpinBox>

#include "comparison_widget.h"

class SpinBoxSearch : public ComparisonWidget {
    QSpinBox* spinBox;
public:
    SpinBoxSearch(QWidget* = nullptr);

    int value() const;
};

#endif // SPINBOXSEARCH_H