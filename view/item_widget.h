#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QLabel>

#include <model/villager/villager.h>

class ItemWidget : public QLabel {
    Q_OBJECT
private:
    Villager* item;

protected:
    void mouseReleaseEvent(QMouseEvent*) override;

public:
    ItemWidget(Villager*, QWidget* = nullptr);

    Villager* getItem() const;
    void setItem(Villager*);

    void updateText();

signals:
    void clicked();
};

#endif // ITEMWIDGET_H