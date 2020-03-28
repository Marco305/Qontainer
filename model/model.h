#ifndef MODEL_H
#define MODEL_H

#include <QFile>

#include <model/villager/villager.h>
#include "container.h"

class Model {
private:
    Container<Villager*>* container;

    bool modified;

public:
    Model();

    ~Model();

    const Container<Villager*>* getContainer() const;

    bool isModified() const;
    void setModified(bool);

    void insertVillager(Villager*);

    void replaceVillager(Villager*, Villager*);

    void removeVillager(Villager*);

    bool loadFromFile(QFile&);

    bool saveToFile(QFile&);
};

#endif // MODEL_H