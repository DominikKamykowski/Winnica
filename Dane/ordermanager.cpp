#include "ordermanager.hpp"

// Singleton
OrderManager * OrderManager::instance = nullptr;


void OrderManager::Create(const QString &filename)
{
    assert(instance == nullptr);
    instance = new OrderManager(filename);
}

void OrderManager::Destroy()
{
    assert(instance != nullptr);
    delete instance;
    instance = nullptr;
}

OrderManager *OrderManager::getInstance()
{
    assert(instance != nullptr);
    return instance;
}

void OrderManager::saveOrders(const QList<Order> &orders) const
{
    QJsonArray jsonArray;
    for (const Order &order : orders)
    {
        jsonArray.append(order.toJson());
    }

    QJsonDocument jsonDoc(jsonArray);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
        file.close();
    }
}

QList<Order> OrderManager::loadOrders()
{
    QList<Order> orders;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonArray jsonArray = jsonDoc.array();
        for (const auto &jsonValue : jsonArray)
        {
            orders.append(Order::fromJson(jsonValue.toObject()));
        }
    }
    return orders;
}

void OrderManager::appendOrder(const Order &order)
{
    QList<Order> orders = loadOrders();
    orders.append(order);
    saveOrders(orders);
}

Order OrderManager::getOrder(const int id)
{
    auto orders = loadOrders();
    return orders.takeAt(id);
}

int OrderManager::getLastOrderId()
{
    QList<Order> orders = loadOrders();

    int lastId = 0;
    for (const Order &order : orders) {
        if (order.getId() > lastId) {
            lastId = order.getId();
        }
    }

    return lastId;
}

bool OrderManager::updateOrder(const Order &updatedOrder)
{
    QList<Order> orders = loadOrders();
    bool found = false;

    for (int i = 0; i < orders.size(); ++i)
    {
        if (orders[i].getId() == updatedOrder.getId())
        {
            orders[i] = updatedOrder; // Zastąp zamówienie
            found = true;
            break;
        }
    }
    if (found)
    {
        saveOrders(orders); // Zapisz zmiany
    }
    return found;
}

bool OrderManager::updateOrderStatus(const int orderId, const Order::Status newStatus)
{
    auto order = getOrder(orderId);

    if(newStatus == Order::Status::Nadane)
    {
        order.setShippingDate(QDate::currentDate());
    }
    if(newStatus == Order::Status::Odebrane)
    {
        order.setDeliveryDate(QDate::currentDate());
    }

    order.setStatus(newStatus);

    return updateOrder(order);
}
