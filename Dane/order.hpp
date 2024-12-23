#ifndef ORDER_HPP
#define ORDER_HPP
#include <QObject>
#include <QDate>
#include <QTableWidget>

class Order
{
public:
    enum Status {
        Nowe,
        Przygotowywane,
        Nadane,
        Odebrane,
        Zagubione
    };

    Order(int id, const QString &factoryNumber, const QString &items,
          const QDate &creationDate, Status status = Status::Nowe, const QDate &shippingDate = QDate(),
          const QDate &deliveryDate = QDate())
        : id(id), factoryNumber(factoryNumber), items(items),
        creationDate(creationDate), shippingDate(shippingDate),
        status(status), deliveryDate(deliveryDate) {}

    QString getStatusString() const;

    void addToTable(QTableWidget *table) const;
    QJsonObject toJson() const;
    static Order fromJson(const QJsonObject &json);

    int getId() const;

    QString getFactoryNumber() const;

    QString getItems() const;

    void setStatus(Status newStatus);

    void setShippingDate(const QDate &newShippingDate);

    QDate getDeliveryDate() const;

    QDate getShippingDate() const;

    void setDeliveryDate(const QDate &newDeliveryDate);

    QDate getCreationDate() const;

    Status getStatus() const;

private:
    int id;
    QString factoryNumber;
    QString items;
    QDate creationDate;
    QDate shippingDate;
    Status status;
    QDate deliveryDate;
};

#endif // ORDER_HPP
