#include <QHBoxLayout>

#include "comparison_widget.h"

ComparisonWidget::ComparisonWidget(QWidget* parent) : QWidget(parent), comboBox(new QComboBox()) {
    comboBox->addItems({">", ">=", "<", "<=", "=", "<empty>"});
    comboBox->setCurrentIndex(OperatorUtil::Operator::UNDEFINED);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(comboBox);
    setLayout(layout);
}

OperatorUtil::Operator ComparisonWidget::currentOperator() const {
    return static_cast<OperatorUtil::Operator>(comboBox->currentIndex());
}