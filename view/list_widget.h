#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>

#include <model/villager/villager.h>
#include "item_widget.h"
#include "item_info_widget.h"
#include "filter.h"

class ListWidget : public QWidget {
    Q_OBJECT
private:
    QList<ItemWidget*> widgets;
    ItemWidget* selected;
    Filter filter;

    void filterItem(ItemWidget*);

public:
    ListWidget(QWidget* = nullptr);

    ItemWidget* getSelected() const;

    ItemWidget* createItem(Villager*);

    void removeSelected();

    void updateSelected();

    bool changeSelected(ItemWidget*);

    void refreshFilter();

public slots:
    void setFilter(const Filter&);

    void removeFiltered();

signals:
    void selectedCleared();

    void itemDeleted(Villager*);
};

#endif // LISTWIDGET_H