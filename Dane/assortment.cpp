#include "assortment.hpp"

Assortment::Assortment(int id, const QString& name, const QString& factoryNumber, const QVector<QString>& ingredients, uint quantity)
    : id(id), name(name), factoryNumber(factoryNumber), ingredients(ingredients), quantity(quantity) {}

Assortment::Assortment() : id(0), quantity(0) {}

int Assortment::getId() const { return id; }
QString Assortment::getName() const { return name; }
QString Assortment::getFactoryNumber() const { return factoryNumber; }
QVector<QString> Assortment::getIngredients() const { return ingredients; }
uint Assortment::getQuantity() const { return quantity; }

void Assortment::setName(const QString& name) { this->name = name; }
void Assortment::setFactoryNumber(const QString& factoryNumber) { this->factoryNumber = factoryNumber; }
void Assortment::setIngredients(const QVector<QString>& ingredients) { this->ingredients = ingredients; }
void Assortment::setQuantity(uint quantity) { this->quantity = quantity; }

QJsonObject Assortment::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["name"] = name;
    json["factoryNumber"] = factoryNumber;
    json["ingredients"] = QJsonArray::fromStringList(ingredients.toList());
    json["quantity"] = static_cast<int>(quantity);
    return json;
}

Assortment Assortment::fromJson(const QJsonObject& json) {
    return Assortment(
        json["id"].toInt(),
        json["name"].toString(),
        json["factoryNumber"].toString(),
        json["ingredients"].toVariant().toStringList().toVector(),
        json["quantity"].toInt()
        );
}
