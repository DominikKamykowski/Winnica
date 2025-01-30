#include "assortmentmanager.hpp"

AssortmentManager* AssortmentManager::instance = nullptr;

AssortmentManager* AssortmentManager::getInstance() {
    if (!instance) {
        instance = new AssortmentManager();
    }
    return instance;
}

AssortmentManager::AssortmentManager() : lastId(0)
{
    loadFromFile("/home/dominik/Projekty/Projekt/assortment.json");
}

void AssortmentManager::addAssortment(const Assortment& assortment) {
    assortments.append(assortment);
    if (assortment.getId() > lastId) {
        lastId = assortment.getId();
    }
}

void AssortmentManager::updateAssortment(const Assortment& assortment) {
    for (Assortment& a : assortments) {
        if (a.getId() == assortment.getId()) {
            a = assortment;
        }
    }
    saveToFile("/home/dominik/Projekty/Projekt/assortment.json");
}

void AssortmentManager::removeAssortment(int id) {
    assortments.erase(
        std::remove_if(assortments.begin(), assortments.end(), [id](const Assortment& a) {
            return a.getId() == id;
        }),
        assortments.end()
        );
}

QList<Assortment> AssortmentManager::getAssortments() const {
    return assortments;
}

void AssortmentManager::appendAssortment(const Assortment& assortment)
{
    addAssortment(assortment); // Dodajemy do wewnętrznej listy
    saveToFile("/home/dominik/Projekty/Projekt/assortment.json");
}


Assortment AssortmentManager::getAssortmentById(int id) const {

    for (const Assortment& a : assortments) {
        if (a.getId() == id) {
            return a;
        }
    }
    qDebug()<<"brak";
    return Assortment(); // Pusty asortyment, jeśli nie znaleziono
}

bool AssortmentManager::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format: Expected an array";
        return false;
    }

    assortments.clear();
    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        assortments.append(Assortment::fromJson(value.toObject()));
    }

    // Zaktualizuj ostatnie ID
    lastId = 0;
    for (const Assortment& a : assortments) {
        if (a.getId() > lastId) {
            lastId = a.getId();
        }
    }

    return true;
}

bool AssortmentManager::saveToFile(const QString& filePath) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonArray array;
    for (const Assortment& a : assortments) {
        array.append(a.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
    return true;
}

int AssortmentManager::getNextId() {
    return ++lastId;
}
