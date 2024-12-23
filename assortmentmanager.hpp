#ifndef ASSORTMENTMANAGER_HPP
#define ASSORTMENTMANAGER_HPP

#include <QList>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "Dane/assortment.hpp"

class AssortmentManager {
public:

    static AssortmentManager* getInstance();

    void addAssortment(const Assortment& assortment);
    void updateAssortment(const Assortment& assortment);
    void removeAssortment(int id);
    void appendAssortment(const Assortment& assortment);

    QList<Assortment> getAssortments() const;
    Assortment getAssortmentById(int id) const;

    bool loadFromFile(const QString& filePath);
    bool saveToFile(const QString& filePath) const;

    int getNextId();
    AssortmentManager();

private:
    ~AssortmentManager() = default;

    QList<Assortment> assortments{};
    int lastId;

    static AssortmentManager* instance;
};

#endif // ASSORTMENTMANAGER_HPP
