#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QStyle>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QInputDialog>

#include "main_window.h"
#include "create_edit_dialog.h"
#include "search_widget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), model(new Model()) {
    setMinimumSize(1200, 600);

    // center window
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()
    ));

    setWindowIcon(QIcon(":/icon.png"));

    // menu and tool bar
    QMenu* fileMenu = menuBar()->addMenu("File");
    QToolBar* fileToolBar = addToolBar("File");

    QAction* saveAction = new QAction(QIcon(":/save.png"), "Save", this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip("Save the data to disk");
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    fileMenu->addSeparator();

    QAction* exitAction = new QAction(QIcon(":/exit.png"), "Exit", this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

    QMenu* villagerMenu = menuBar()->addMenu("Villager");
    QToolBar* villagerToolBar = addToolBar("Villager");

    QAction* newAction = new QAction(QIcon(":/new.png"), "New", this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip("Create a new villager");
    connect(newAction, &QAction::triggered, this, [this]() {
        CreateEditDialog* dialog = new CreateEditDialog(this);
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        connect(dialog, &CreateEditDialog::itemCreated, this, [this](Villager* item) {
            model->insertVillager(item);
            createItem(item);
        });
        dialog->show();
    });
    villagerMenu->addAction(newAction);
    villagerToolBar->addAction(newAction);

    QAction* taxAction = new QAction(QIcon(":/tax.png"), "Base Tax", this);
    taxAction->setStatusTip("Set the base tax");
    connect(taxAction, &QAction::triggered, this, [this]() {
        bool ok;
        double baseTax = QInputDialog::getDouble(this, "Qontainer", "Base Tax:",
                Villager::getBaseTax(), 0.0, 99999999.0, 1, &ok, Qt::MSWindowsFixedSizeDialogHint);
        if (ok) {
            Villager::setBaseTax(baseTax);
            model->setModified(true);
            if (list->getSelected() != nullptr) {
                info->update(list->getSelected()->getItem());
            }
            list->refreshFilter();
        }
    });
    villagerMenu->addAction(taxAction);

    // central widget
    QWidget* centralWidget = new QWidget();
    QHBoxLayout* centralLayout = new QHBoxLayout();
    centralLayout->setSpacing(30);

    info = new ItemInfoWidget();
    connect(info, &ItemInfoWidget::itemDeleted, this, &MainWindow::deleteItem);
    connect(info, &ItemInfoWidget::itemEdited, this, [this](Villager* oldItem, Villager* newItem) {
        if (oldItem != nullptr) {
            model->replaceVillager(oldItem, newItem);
            list->getSelected()->setItem(newItem);
        }
        model->setModified(true);
        info->update(newItem);
        list->updateSelected();
    });

    QFrame* panel = new QFrame();
    panel->setFrameStyle(QFrame::StyledPanel);
    QHBoxLayout* panelLayout = new QHBoxLayout();
    panelLayout->setSpacing(30);

    list = new ListWidget();
    connect(list, &ListWidget::selectedCleared, this, [this]() {
        info->update();
    });
    connect(list, &ListWidget::itemDeleted, this, &MainWindow::deleteItem);
    QScrollArea* scrollList = new QScrollArea();
    scrollList->setFrameStyle(0);
    scrollList->setWidgetResizable(true);
    scrollList->setWidget(list);

    panelLayout->addWidget(scrollList, 5);
    panelLayout->addWidget(info, 5);
    panel->setLayout(panelLayout);

    SearchWidget* search = new SearchWidget();
    connect(search, &SearchWidget::applyFilter, list, &ListWidget::setFilter);
    connect(search, &SearchWidget::removeFiltered, list, &ListWidget::removeFiltered);

    centralLayout->addWidget(search, 4);
    centralLayout->addWidget(panel, 6);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    loadData();
    for (auto it = model->getContainer()->begin(); it != model->getContainer()->end(); ++it) {
        createItem(*it);
    }
}

MainWindow::~MainWindow() {
    delete model;
}

void MainWindow::createItem(Villager* item) {
    ItemWidget* iw = list->createItem(item);
    connect(iw, &ItemWidget::clicked, this, [this, iw]() {
        if (list->changeSelected(iw)) {
            info->update(iw->getItem());
        }
    });
}

void MainWindow::deleteItem(Villager* item) {
    if (list->getSelected() != nullptr && item == list->getSelected()->getItem()) {
        list->removeSelected();
    }
    info->update();
    model->removeVillager(item);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (trySave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::save() {
    return saveData();
}

bool MainWindow::trySave() {
    if (!model->isModified()) {
        return true;
    }

    QMessageBox::StandardButton button = QMessageBox::warning(this, "Qontainer",
                                                              "The data has been modified.\n"
                                                              "Do you want to save your changes?",
                                                              QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (button) {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            return true;
    }
}

void MainWindow::loadData() {
    QFile file("data.json");
    if (!model->loadFromFile(file)) {
        QMessageBox::warning(this, "Qontainer", QString("Cannot read file %1:\n%2.")
                .arg(QDir::toNativeSeparators(file.fileName()), file.errorString()));
    }
}

bool MainWindow::saveData() {
    QFile file("data.json");
    if (!model->saveToFile(file)) {
        QMessageBox::warning(this, "Qontainer", QString("Cannot save file %1:\n%2.")
                .arg(QDir::toNativeSeparators(file.fileName()), file.errorString()));
        return false;
    }

    return true;
}
