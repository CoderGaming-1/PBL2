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

        QVector<Order> filteredOrders = getFilteredOrders(startDateEdit->dateTime(), endDateEdit->dateTime());
        bool orderFound = false;

        for (const Order& order : filteredOrders) {
            if (order.orderID == orderID) {
                qDebug() << "Order found:" << order.orderID;
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





QVector<Order> StatisticWindow::getAllOrders() {
    QVector<Order> orders;

    QFile file("C:/AllFiles/Code/C++/Data/orders.txt");
    if (!file.exists()) {
        qDebug() << "File does not exist at:" << file.fileName();
        return orders;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading at:" << file.fileName();
        return orders;
    }

    qDebug() << "File successfully opened.";
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Line read:" << line;

        QStringList parts = line.split(" ");
        qDebug() << "Split parts:" << parts;

        if (parts.size() >= 6) {
            // Read the first four fields: OrderID, Name Client, TotalPayment, Date Purchase
            QString orderID = parts[0];
            QString nameClient = parts[1];
            QString totalPayment = parts[2];
            QString datePurchase = parts[3] + " " + parts[4];

            // Parse the date field into QDateTime
            QDateTime date = QDateTime::fromString(datePurchase, "dd/MM/yyyy HH:mm");
            if (!date.isValid()) {
                qDebug() << "Invalid date format for:" << datePurchase;
                continue;
            }

            // Process product details after the first four fields
            QString productDetails;
            int currentIndex = 5;
            while (currentIndex < parts.size()) {
                productDetails += parts[currentIndex++];
                if (currentIndex < parts.size()) {
                    productDetails += " ";
                }
            }

            // Create an order object with the parsed details
            Order order = {orderID, nameClient, totalPayment.toDouble(), productDetails, date};
            orders.append(order);

            qDebug() << "Order parsed:" << order.orderID << order.nameClient << order.totalPayment
                     << order.productDetails << order.date.toString();
        }
    }

    file.close();
    return orders;
}

QVector<Order> StatisticWindow::getFilteredOrders(const QDateTime& startDate, const QDateTime& endDate) {
    QVector<Order> allOrders = getAllOrders();
    QVector<Order> filteredOrders;

    qDebug() << "Total orders retrieved:" << allOrders.size();

    for (const Order& order : allOrders) {
        if (order.date >= startDate && order.date <= endDate) {
            filteredOrders.append(order);
            qDebug() << "Filtered Order:" << order.orderID << order.nameClient << order.date.toString();
        }
    }

    qDebug() << "Filtered orders count:" << filteredOrders.size();
    return filteredOrders;
}


void StatisticWindow::filterOrdersByDate(const QDateTime& startDate, const QDateTime& endDate, QTableWidget* table) {
    QVector<Order> filteredOrders = getFilteredOrders(startDate, endDate);

    table->setRowCount(0); // Clear existing rows

    if (filteredOrders.isEmpty()) {
        qDebug() << "No orders found in the specified date range.";
    }

    for (const Order& order : filteredOrders) {
        qDebug() << "Adding row for Order ID:" << order.orderID; // Debug output
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(order.orderID));
        table->setItem(row, 1, new QTableWidgetItem(order.nameClient));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(order.totalPayment, 'f', 2)));
        table->setItem(row, 3, new QTableWidgetItem(order.date.toString("dd/MM/yyyy HH:mm")));

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
void StatisticWindow::showOrderDetails(const Order& order) {
    // You can open a new window to display the order details,
    // like opening a DetailOrderWindow or just printing the details to the console

    qDebug() << "Order ID:" << order.orderID;
    qDebug() << "Client Name:" << order.nameClient;
    qDebug() << "Date:" << order.date.toString();
    qDebug() << "Products:" << order.productDetails;

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
