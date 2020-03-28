#include <QVBoxLayout>

#include "list_widget.h"

ListWidget::ListWidget(QWidget* parent) : QWidget(parent), selected(nullptr) {
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(5);
    setLayout(layout);
}

ItemWidget* ListWidget::getSelected() const {
    return selected;
}

ItemWidget* ListWidget::createItem(Villager* item) {
    ItemWidget* iw = new ItemWidget(item);
    widgets.push_back(iw);
    filterItem(iw);
    return iw;
}

void ListWidget::removeSelected() {
    layout()->removeWidget(selected);
    widgets.removeOne(selected);
    delete selected;
    selected = nullptr;
}

void ListWidget::updateSelected() {
    selected->updateText();

    if (!filter.accept(selected->getItem())) {
        layout()->removeWidget(selected);
        selected->hide();
        selected->setStyleSheet("");
        selected = nullptr;
        emit selectedCleared();
    }
}

bool ListWidget::changeSelected(ItemWidget* iw) {
    if (selected != iw) {
        if (selected != nullptr) {
            selected->setStyleSheet("");
        }
        selected = iw;
        selected->setStyleSheet("background-color: lightgray;");
        return true;
    }
    return false;
}

void ListWidget::setFilter(const Filter& filter) {
    this->filter = filter;

    refreshFilter();
}

void ListWidget::refreshFilter() {
    // clear current filter
    while (QLayoutItem* item = layout()->takeAt(0)) {
        item->widget()->hide();
        delete item;
    }
    if (selected != nullptr && !filter.accept(selected->getItem())) {
        selected->setStyleSheet("");
        selected = nullptr;
        emit selectedCleared();
    }

    // apply new filter
    for (auto it = widgets.begin(); it != widgets.end(); ++it) {
        filterItem(*it);
    }
}

void ListWidget::filterItem(ItemWidget* iw) {
    if (filter.accept(iw->getItem())) {
        layout()->addWidget(iw);
        iw->show();
    }
}

void ListWidget::removeFiltered() {
    for (auto it = widgets.begin(); it != widgets.end();) {
        ItemWidget* iw = *it;
        if (iw->isVisible()) {
            if (iw == selected) {
                selected = nullptr;
            }
            layout()->removeWidget(iw);
            it = widgets.erase(it);
            emit itemDeleted(iw->getItem());
            delete iw;
        } else {
            ++it;
        }
    }
    setFilter(Filter());
}
