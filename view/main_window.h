#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <model/model.h>
#include "list_widget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Model* model;
    ItemInfoWidget* info;
    ListWidget* list;

    void createItem(Villager*);

protected:
    void closeEvent(QCloseEvent*) override;

public:
    MainWindow(QWidget* = nullptr);

    ~MainWindow();

    bool trySave();

    void loadData();

    bool saveData();

private slots:
    bool save();

    void deleteItem(Villager*);
};

#endif // MAINWINDOW_H