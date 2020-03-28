#include "item_widget.h"

ItemWidget::ItemWidget(Villager* item, QWidget* parent) : QLabel(parent), item(item) {
    setFixedHeight(40);
    updateText();
}

void ItemWidget::mouseReleaseEvent(QMouseEvent* event) {
    QLabel::mouseReleaseEvent(event);
    emit clicked();
}

Villager* ItemWidget::getItem() const {
    return item;
}

void ItemWidget::setItem(Villager* item) {
    this->item = item;
}

void ItemWidget::updateText() {
    setText(QString::fromStdString("<i>" + item->getType()->name()) + "</i> " + QString::fromStdString(item->getName()));
}
