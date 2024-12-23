#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <QString>
#include <QJsonObject>
#include <QTableWidget>

class Ingredient
{
public:
    Ingredient(int id, const QString &name, double stockQuantity)
        : id(id), name(name), stockQuantity(stockQuantity) {}

    // Gettery
    int getId() const;
    QString getName() const;
    double getStockQuantity() const;

    // Settery
    void setName(const QString &newName);
    void setStockQuantity(double newQuantity);

    // Operacje na magazynie
    bool increaseStock(double quantity);
    bool decreaseStock(double quantity);

    // Serializacja
    QJsonObject toJson() const;
    static Ingredient fromJson(const QJsonObject &json);

    // Prezentacja w tabeli
    void addToTable(QTableWidget *table) const;

private:
    int id;                // Unikalny identyfikator składnika
    QString name;          // Nazwa składnika
    double stockQuantity;  // Ilość w magazynie
};

#endif // INGREDIENT_HPP
