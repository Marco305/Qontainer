#ifndef COMPARISONWIDGET_H
#define COMPARISONWIDGET_H

#include <QWidget>
#include <QComboBox>

#include "operator_util.h"

class ComparisonWidget : public QWidget {
private:
    QComboBox* comboBox;

public:
    ComparisonWidget(QWidget* = nullptr);

    OperatorUtil::Operator currentOperator() const;
};

#endif // COMPARISONWIDGET_H