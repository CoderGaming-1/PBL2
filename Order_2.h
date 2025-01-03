#ifndef ORDER_2_H
#define ORDER_2_H

#include <QString>
#include <QDateTime>
#include "OrderItem.h"

class Order_2 {
public:
    QString orderId;
    QString customerName;
    QVector<OrderItem> items;
    double totalAmount;
    QDateTime datetime;

    void setItems(const QVector<OrderItem>& newItems) {
        items = newItems;
    }
    // Constructor (optional, if needed)
    // Order_2(const QString& orderID, const QString& nameClient, double totalPayment, const QString& productDetails, const QDateTime& date)
    //     : orderID(orderID), nameClient(nameClient), totalPayment(totalPayment), productDetails(productDetails), date(date) {}
};

#endif // ORDER_2_H
