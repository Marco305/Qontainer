#ifndef ITEMINFOWIDGET_H
#define ITEMINFOWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>

#include <model/villager/villager.h>

class ItemInfoWidget : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* layout;

    static void clearWidgets(QLayout*);

public:
    ItemInfoWidget(QWidget* = nullptr);

    void update(Villager* = nullptr);

signals:
    void itemEdited(Villager*, Villager*);

    void itemDeleted(Villager*);
};

#endif // ITEMINFOWIDGET_H