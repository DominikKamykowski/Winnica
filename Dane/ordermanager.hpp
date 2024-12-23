#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include <QList>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "order.hpp"

class OrderManager {
public:
    // Singleton
    static void Create(const QString &filename);
    static void Destroy();
    static OrderManager* getInstance();

    OrderManager(const QString &filename) : filename(filename) {}

    void saveOrders(const QList<Order> &orders) const;
    QList<Order> loadOrders();
    Order getOrder(const int id);
    void appendOrder(const Order &order);
    int getLastOrderId();
    bool updateOrder(const Order &updatedOrder);

    bool updateOrderStatus(const int orderId,const  Order::Status newStatus);

private:
    static OrderManager *instance;                     //!< Instancja klasy.

    QString filename;
};

#endif // ORDERMANAGER_HPP
