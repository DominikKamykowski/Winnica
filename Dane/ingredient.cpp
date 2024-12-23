#include "ingredient.hpp"

// Gettery
int Ingredient::getId() const { return id; }
QString Ingredient::getName() const { return name; }
double Ingredient::getStockQuantity() const { return stockQuantity; }

// Settery
void Ingredient::setName(const QString &newName) { name = newName; }
void Ingredient::setStockQuantity(double newQuantity) { stockQuantity = newQuantity; }

// Operacje na magazynie
bool Ingredient::increaseStock(double quantity)
{
    if (quantity <= 0)
        return false;
    stockQuantity += quantity;
    return true;
}

bool Ingredient::decreaseStock(double quantity)
{
    if (quantity <= 0 || quantity > stockQuantity)
        return false;
    stockQuantity -= quantity;
    return true;
}

// Serializacja
QJsonObject Ingredient::toJson() const
{
    QJsonObject json;
    json["id"] = id;
    json["name"] = name;
    json["stockQuantity"] = stockQuantity;
    return json;
}

Ingredient Ingredient::fromJson(const QJsonObject &json)
{
    int id = json["id"].toInt();
    QString name = json["name"].toString();
    double stockQuantity = json["stockQuantity"].toDouble();
    QString unit = json["unit"].toString();
    return Ingredient(id, name, stockQuantity);
}

// Dodawanie do tabeli
void Ingredient::addToTable(QTableWidget *table) const
{
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    table->setItem(row, 1, new QTableWidgetItem(name));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(stockQuantity)));
}
