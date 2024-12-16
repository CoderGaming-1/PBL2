#ifndef DETAILORDERWINDOW_H
#define DETAILORDERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QDateTime>
#include "Order.h"  // Assuming you have an Order class that represents an order

class DetailOrderWindow : public QDialog {
    Q_OBJECT

public:
    // Constructor that accepts the order to display
    explicit DetailOrderWindow(const Order& order, QWidget* parent = nullptr);

private:
    // UI elements for displaying the order details
    QLabel* orderIDLabel;
    QLabel* clientNameLabel;
    QLabel* totalPaymentLabel;
    QLabel* dateLabel;

    // Order object to hold the order details
    Order order;  // Member variable to store the order data
};

#endif // DETAILORDERWINDOW_H
