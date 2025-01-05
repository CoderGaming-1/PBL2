#ifndef STATISTICWINDOW_H
#define STATISTICWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include "Order_2.h"

class StatisticWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticWindow(QWidget *parent = nullptr);
    void filterOrdersByDate(const QDateTime& startDate, const QDateTime& endDate, QTableWidget* table);
    void showOrderDetails(const Order_2& order);
private slots:
    void onResearchButtonClicked();  // Slot to filter data based on the date range
    void onRowClicked(int row, int column);  // Slot to handle row click
    void onAscendButtonClicked();
    void onDescendButtonClicked();

private:
    QDateTimeEdit* startDateEdit;    // Start date field
    QDateTimeEdit* endDateEdit;      // End date field
    QPushButton* researchButton;     // Button to trigger the filtering
    QTableWidget* ordersTable;       // Table to display the filtered orders
    QPushButton* ascendButton;
    QPushButton* descendButton;

    QVector<Order_2> getAllOrders();                // Fetch all orders
    QVector<Order_2> getFilteredOrders(const QDateTime& startDate, const QDateTime& endDate);  // Filter orders by date
};

#endif // STATISTICWINDOW_H
