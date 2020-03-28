#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "model.h"

Model::Model() : container(new Container<Villager*>()), modified(false) {}

Model::~Model() {
    delete container;
}

const Container<Villager*>* Model::getContainer() const {
    return container;
}

bool Model::isModified() const {
    return modified;
}

void Model::setModified(bool modified) {
    this->modified = modified;
}

void Model::insertVillager(Villager* villager) {
    container->insert(villager);
    modified = true;
}

void Model::replaceVillager(Villager* oldVillager, Villager* newVillager) {
    for (auto it = container->begin(); it != container->end(); ++it) {
        if (*it == oldVillager) {
            delete *it;
            *it = newVillager;
            modified = true;
            break;
        }
    }
}

void Model::removeVillager(Villager* villager) {
    container->remove(villager);
    delete villager;
    modified = true;
}

bool Model::loadFromFile(QFile& file) {
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) return false;
    } else {
        if (!file.open(QIODevice::ReadWrite)) return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) return true;
    if (!doc.isObject()) return false;

    QJsonObject obj = doc.object();

    Villager::setBaseTax(obj["baseTax"].toDouble(50.0));

    QJsonArray array = obj["villagers"].toArray();
    for (auto it = array.begin(); it != array.end(); ++it) {
        if (!it->isObject()) continue;
        Villager* p = Villager::createFromJson(it->toObject());
        if (p != nullptr) {
            container->insert(p);
        }
    }

    return true;
}

bool Model::saveToFile(QFile& file) {
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonObject obj;

    obj["baseTax"] = Villager::getBaseTax();

    QJsonArray array;
    for (auto it = container->begin(); it != container->end(); ++it) {
        QJsonObject v;
        (*it)->saveToJson(v);
        array.append(v);
    }
    obj["villagers"] = array;

    file.write(QJsonDocument(obj).toJson());

    modified = false;

    return true;
}
