#include "StatisticWindow.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QHeaderView>
#include "DetailOrderWindow.h"
StatisticWindow::StatisticWindow(QWidget *parent)
    : QWidget(parent) {
    // Initialize UI elements
    startDateEdit = new QDateTimeEdit(this);
    endDateEdit = new QDateTimeEdit(this);
    researchButton = new QPushButton("Research", this);
    ordersTable = new QTableWidget(this);

    // Set up date edit widgets to display only the date (no time)
    startDateEdit->setDisplayFormat("dd/MM/yyyy");
    endDateEdit->setDisplayFormat("dd/MM/yyyy");

    // Set calendar popup for date selection
    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);

    // Set the default date to today's date
    startDateEdit->setDate(QDate::currentDate());
    endDateEdit->setDate(QDate::currentDate());

    ordersTable->setColumnCount(5);  // Update to 5 to add the "Detail" column
    ordersTable->setHorizontalHeaderLabels({"OrderID", "Name Client", "TotalPayment", "Date Purchase", "More Information"});

    // Set the table to stretch horizontally
    ordersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set up layout for the window
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* dateLayout = new QHBoxLayout();
    dateLayout->addWidget(new QLabel("Start Date:"));
    dateLayout->addWidget(startDateEdit);
    dateLayout->addWidget(new QLabel("End Date:"));
    dateLayout->addWidget(endDateEdit);
    mainLayout->addLayout(dateLayout);

    mainLayout->addWidget(researchButton);
    mainLayout->addWidget(ordersTable);

    // Set the layout for the window
    setLayout(mainLayout);

    // Connect button click to the appropriate slot
    connect(researchButton, &QPushButton::clicked, this, &StatisticWindow::onResearchButtonClicked);

    // Connect row click to the onRowClicked slot (passing row and column as arguments)
    connect(ordersTable, &QTableWidget::cellClicked, this, &StatisticWindow::onRowClicked);

    // Populate the table with initial data
    filterOrdersByDate(QDateTime::fromString("01/01/2000", "dd/MM/yyyy"), QDateTime::currentDateTime(), ordersTable);
}


// Inside your `StatisticWindow` class where you are calling `showOrderDetails`
void StatisticWindow::onRowClicked(int row, int column) {
    qDebug() << "Row clicked:" << row << ", Column clicked:" << column;

    if (column == 1) {
        QString orderID = ordersTable->item(row, 0)->text();
        qDebug() << "Order ID:" << orderID;

        QVector<Order_2> filteredOrders = getFilteredOrders(startDateEdit->dateTime(), endDateEdit->dateTime());
        bool orderFound = false;

        for (const Order_2& order : filteredOrders) {
            if (order.orderId == orderID) {
                qDebug() << "Order found:" << order.orderId;
                showOrderDetails(order); // Call the showOrderDetails function here
                orderFound = true;
                break;
            }
        }

        if (!orderFound) {
            qDebug() << "Order not found for OrderID:" << orderID;
        }
    }
}

bool parseOrder(const QString& line, Order_2& order) {
    QStringList parts;
    QString itemsStr, datetimeStr;

    // Custom parsing logic for the line
    int pos = 0;
    if ((pos = line.indexOf(',')) == -1) return false;
    order.orderId = line.left(pos);
    QString remaining = line.mid(pos + 1);

    // Extract customer name
    pos = remaining.indexOf(',');
    if (pos == -1) return false;
    order.customerName = remaining.left(pos).trimmed();
    remaining = remaining.mid(pos + 1);

    // Extract quoted items field
    if (remaining.startsWith('"')) {
        pos = remaining.indexOf('"', 1);
        if (pos == -1) return false;
        itemsStr = remaining.mid(1, pos - 1);
        remaining = remaining.mid(pos + 2); // Skip closing quote and comma
    } else {
        pos = remaining.indexOf(',');
        if (pos == -1) return false;
        itemsStr = remaining.left(pos);
        remaining = remaining.mid(pos + 1);
    }

    // Extract total amount
    pos = remaining.indexOf(',');
    if (pos == -1) return false;
    order.totalAmount = remaining.left(pos).toDouble();
    datetimeStr = remaining.mid(pos + 1);

    // Parse datetime
    order.datetime = QDateTime::fromString(datetimeStr.trimmed(), "yyyy-MM-dd HH:mm:ss");
    if (!order.datetime.isValid()) {
        qDebug() << "Invalid datetime format:" << datetimeStr;
        return false;
    }

    // Parse items field
    QVector<OrderItem> items;
    QStringList itemList = itemsStr.split(';', Qt::SkipEmptyParts);
    for (const QString& itemStr : itemList) {
        QStringList itemParts = itemStr.split(',');
        if (itemParts.size() == 2) {
            bool ok1 = false, ok2 = false;
            int productId = itemParts[0].toInt(&ok1);
            int quantity = itemParts[1].toInt(&ok2);
            if (ok1 && ok2) {
                items.append(OrderItem(productId, quantity));
            }
        }
    }
    order.setItems(items);

    return true;
}

QVector<Order_2> StatisticWindow::getAllOrders() {
    // QVector<Order> orders;

    // QFile file("C:/AllFiles/Code/C++/Data/orders.txt");
    // if (!file.exists()) {
    //     qDebug() << "File does not exist at:" << file.fileName();
    //     return orders;
    // }
    // if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qDebug() << "Could not open file for reading at:" << file.fileName();
    //     return orders;
    // }

    // qDebug() << "File successfully opened.";
    // QTextStream in(&file);
    // while (!in.atEnd()) {
    //     QString line = in.readLine();
    //     qDebug() << "Line read:" << line;

    //     QStringList parts = line.split(",", Qt::SkipEmptyParts);
    //     qDebug() << "Split parts:" << parts;

    //     if (parts.size() >= 6) {
    //         // Read the first four fields: OrderID, Name Client, TotalPayment, Date Purchase
    //         QString orderID = parts[0];
    //         QString nameClient = parts[1];
    //         QString totalPayment = parts[3];
    //         QString datePurchase = parts[4] + " " + parts[5];

    //         // Parse the date field into QDateTime
    //         QDateTime date = QDateTime::fromString(datePurchase, "dd/MM/yyyy HH:mm");
    //         if (!date.isValid()) {
    //             qDebug() << "Invalid date format for:" << datePurchase;
    //             continue;
    //         }

    //         // Process product details after the first four fields
    //         QString productDetails;
    //         int currentIndex = 5;
    //         while (currentIndex < parts.size()) {
    //             productDetails += parts[currentIndex++];
    //             if (currentIndex < parts.size()) {
    //                 productDetails += " ";
    //             }
    //         }

    //         // Create an order object with the parsed details
    //         Order_2 order = {orderID, nameClient, totalPayment.toDouble(), productDetails, date};
    //         orders.append(order);

    //         qDebug() << "Order parsed:" << order.orderID << order.nameClient << order.totalPayment
    //                  << order.productDetails << order.date.toString();
    //     }
    // }

    // file.close();
    // return orders;
    QVector<Order_2> orders;

    QFile file("C:/AllFiles/Code/C++/Data/orders.txt");
    if (!file.exists()) {
        qDebug() << "File does not exist at:" << file.fileName();
        return orders;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading at:" << file.fileName();
        return orders;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            Order_2 order;
            if (parseOrder(line, order)) {
                orders.append(order);
            } else {
                qDebug() << "Failed to parse line:" << line;
            }
        }
    }

    file.close();
    for (const Order_2& order : orders) {
        qDebug() << "Order ID:" << order.orderId
                 << "Customer Name:" << order.customerName
                 << "Total Amount:" << order.totalAmount
                 << "Date:" << order.datetime.toString()
                 << "Items:" << order.items.size();
    }
    return orders;
}

QVector<Order_2> StatisticWindow::getFilteredOrders(const QDateTime& startDate, const QDateTime& endDate) {
    QVector<Order_2> allOrders = getAllOrders();
    QVector<Order_2> filteredOrders;

    qDebug() << "Total orders retrieved:" << allOrders.size();

    for (const Order_2& order : allOrders) {
        if (order.datetime >= startDate && order.datetime <= endDate) {
            filteredOrders.append(order);
            qDebug() << "Filtered Order:" << order.orderId << order.customerName << order.datetime.toString();
        }
    }

    qDebug() << "Filtered orders count:" << filteredOrders.size();
    return filteredOrders;
}


void StatisticWindow::filterOrdersByDate(const QDateTime& startDate, const QDateTime& endDate, QTableWidget* table) {
    QVector<Order_2> filteredOrders = getFilteredOrders(startDate, endDate);

    table->setRowCount(0); // Clear existing rows

    if (filteredOrders.isEmpty()) {
        qDebug() << "No orders found in the specified date range.";
    }

    for (const Order_2& order : filteredOrders) {
        qDebug() << "Adding row for Order ID:" << order.orderId; // Debug output
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(order.orderId));
        table->setItem(row, 1, new QTableWidgetItem(order.customerName));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(order.totalAmount, 'f', 2)));
        table->setItem(row, 3, new QTableWidgetItem(order.datetime.toString("dd/MM/yyyy HH:mm")));

        // Add a button to the "Detail" column
        QPushButton* detailButton = new QPushButton("hint", this);
        detailButton->setFixedSize(155, 30);  // Set size of the button
        table->setCellWidget(row, 4, detailButton);  // Place the button in the 5th column (index 4)

        // Connect the button click to show the order details
        connect(detailButton, &QPushButton::clicked, this, [this, order]() {
            showOrderDetails(order);
        });
    }

    // Adjust the columns to fit content
    table->resizeColumnsToContents();

    // Adjust row heights to fit content
    table->resizeRowsToContents();
    ordersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Force an update to ensure the table is redrawn correctly
    table->update();
}

// In StatisticWindow.cpp
void StatisticWindow::showOrderDetails(const Order_2& order) {
    // You can open a new window to display the order details,
    // like opening a DetailOrderWindow or just printing the details to the console

    qDebug() << "Order ID:" << order.orderId;
    qDebug() << "Client Name:" << order.customerName;
    qDebug() << "Date:" << order.datetime.toString();
    // qDebug() << "Products:" << order.items;

    // Example: You can open a DetailOrderWindow here if you want to show the details in a dialog:
    DetailOrderWindow* detailWindow = new DetailOrderWindow(order, this);
    detailWindow->exec();
}

void StatisticWindow::onResearchButtonClicked() {
    // Get the selected date range
    QDateTime startDate = startDateEdit->dateTime();
    QDateTime endDate = endDateEdit->dateTime();

    // Filter orders by the selected date range and update the table
    filterOrdersByDate(startDate, endDate, ordersTable);
}
