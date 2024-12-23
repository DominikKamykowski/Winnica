#include "order.hpp"
#include <QJsonArray>
#include <QJsonObject>

QString Order::getStatusString() const
{
    switch (status) {
    case Nowe: return "Nowe";
    case Przygotowywane: return "Przygotowywane";
    case Nadane: return "Nadane";
    case Odebrane: return "Odebrane";
    case Zagubione: return "Zagubione";
    default: return "Nieznany";
    }
}

void Order::addToTable(QTableWidget *table) const
{
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    table->setItem(row, 1, new QTableWidgetItem(factoryNumber));
    table->setItem(row, 2, new QTableWidgetItem(items)); // Zmieniono na QString
    table->setItem(row, 3, new QTableWidgetItem(creationDate.toString("yyyy-MM-dd")));
    table->setItem(row, 4, new QTableWidgetItem(shippingDate.toString("yyyy-MM-dd")));
    table->setItem(row, 5, new QTableWidgetItem(getStatusString()));
    table->setItem(row, 6, new QTableWidgetItem(deliveryDate.isValid() ? deliveryDate.toString("yyyy-MM-dd") : "Brak"));
}

QJsonObject Order::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["factoryNumber"] = factoryNumber;
    json["items"] = items; // Zmieniono na QString
    json["creationDate"] = creationDate.toString("yyyy-MM-dd");
    json["shippingDate"] = shippingDate.toString("yyyy-MM-dd");
    json["status"] = status;
    json["deliveryDate"] = deliveryDate.isValid() ? deliveryDate.toString("yyyy-MM-dd") : QString();
    return json;
}

Order Order::fromJson(const QJsonObject &json)
{
    int id = json["id"].toInt();
    QString factoryNumber = json["factoryNumber"].toString();
    QString items = json["items"].toString(); // Zmieniono na QString
    QDate creationDate = QDate::fromString(json["creationDate"].toString(), "yyyy-MM-dd");
    QDate shippingDate = QDate::fromString(json["shippingDate"].toString(), "yyyy-MM-dd");
    Order::Status status = static_cast<Order::Status>(json["status"].toInt());
    QDate deliveryDate = QDate::fromString(json["deliveryDate"].toString(), "yyyy-MM-dd");
    return Order(id, factoryNumber, items, creationDate, status, shippingDate, deliveryDate);
}

int Order::getId() const
{
    return id;
}

QString Order::getFactoryNumber() const
{
    return factoryNumber;
}

QString Order::getItems() const
{
    return items;
}

void Order::setStatus(Status newStatus)
{
    status = newStatus;
}

void Order::setShippingDate(const QDate &newShippingDate)
{
    shippingDate = newShippingDate;
}

QDate Order::getDeliveryDate() const
{
    return deliveryDate;
}

QDate Order::getShippingDate() const
{
    return shippingDate;
}

void Order::setDeliveryDate(const QDate &newDeliveryDate)
{
    deliveryDate = newDeliveryDate;
}

QDate Order::getCreationDate() const
{
    return creationDate;
}

Order::Status Order::getStatus() const
{
    return status;
}
