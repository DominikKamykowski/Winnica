#ifndef ASSORTMENT_HPP
#define ASSORTMENT_HPP

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

class Assortment {
public:
    Assortment(int id, const QString& name, const QString& factoryNumber, const QVector<QString>& ingredients, uint quantity);
    Assortment();

    int getId() const;
    QString getName() const;
    QString getFactoryNumber() const;
    QVector<QString> getIngredients() const;
    uint getQuantity() const;

    void setName(const QString& name);
    void setFactoryNumber(const QString& factoryNumber);
    void setIngredients(const QVector<QString>& ingredients);
    void setQuantity(uint quantity);

    QJsonObject toJson() const;
    static Assortment fromJson(const QJsonObject& json);

private:
    int id;
    QString name;
    QString factoryNumber;
    QVector<QString> ingredients;
    uint quantity;
};

#endif // ASSORTMENT_HPP
