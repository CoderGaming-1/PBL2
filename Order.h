#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDateTime>

class Order {
public:
    QString orderID;
    QString nameClient;
    double totalPayment;
    QString productDetails;
    QDateTime date;

    // Constructor (optional, if needed)
    Order(const QString& orderID, const QString& nameClient, double totalPayment, const QString& productDetails, const QDateTime& date)
        : orderID(orderID), nameClient(nameClient), totalPayment(totalPayment), productDetails(productDetails), date(date) {}
};

#endif // ORDER_H
