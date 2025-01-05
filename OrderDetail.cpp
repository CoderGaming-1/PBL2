#include "OrderDetail.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QLineEdit>
#include <QMessageBox>
OrderDetail::OrderDetail(QWidget* parent) : QMainWindow(parent) {
    setupUI();

}

OrderDetail::~OrderDetail() = default;

void OrderDetail::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Title Section
    QHBoxLayout* titleLayout = new QHBoxLayout();

    QLabel* titleLabel = new QLabel("Fast Food");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel* dateLabel = new QLabel(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    QLabel* staffLabel = new QLabel("Staff: Hoang");
    orderCodeLabel = new QLabel("Code: 0000");  // Placeholder for order code
    QVBoxLayout* dateStaffLayout = new QVBoxLayout();
    dateStaffLayout->addWidget(dateLabel);
    dateStaffLayout->addWidget(staffLabel);
    dateStaffLayout->addWidget(orderCodeLabel);

    QVBoxLayout* customerLayout = new QVBoxLayout();
    QLabel* customerLabel = new QLabel("Customer:");
    customerField = new QLineEdit();
    customerLayout->addWidget(customerLabel);
    customerLayout->addWidget(customerField);

    QHBoxLayout* titleLeftLayout = new QHBoxLayout();
    titleLeftLayout->addLayout(customerLayout);
    titleLeftLayout->addStretch();

    QVBoxLayout* titleMainLayout = new QVBoxLayout();
    titleMainLayout->addLayout(titleLeftLayout);
    titleMainLayout->addWidget(titleLabel);

    titleLayout->addLayout(titleMainLayout, 1);  // Stretch to center
    titleLayout->addLayout(dateStaffLayout);

    mainLayout->addLayout(titleLayout);

    // Table Section
    itemsTable = new QTableWidget(this);
    itemsTable->setColumnCount(4); // Update to 4 columns
    QStringList headers = {"Item Name", "Quantity", "Price", "Product ID"}; // Add "Product ID"
    itemsTable->setHorizontalHeaderLabels(headers);
    itemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    itemsTable->setSelectionMode(QAbstractItemView::NoSelection);
    itemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(itemsTable);

    // Total Price Section
    QHBoxLayout* totalLayout = new QHBoxLayout();
    QLabel* totalLabel = new QLabel("Total Price:");
    totalPriceLabel = new QLabel("0.00");
    totalPriceLabel->setStyleSheet("font-weight: bold;");

    totalLayout->addStretch();
    totalLayout->addWidget(totalLabel);
    totalLayout->addWidget(totalPriceLabel);

    mainLayout->addLayout(totalLayout);

    // Bottom Section
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* printButton = new QPushButton("Print");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonLayout->addStretch();
    buttonLayout->addWidget(printButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connect buttons
    connect(printButton, &QPushButton::clicked, this, [this]() {
        handlePrint(filteredProducts);  // Pass filteredProducts when the button is clicked
    });
    connect(cancelButton, &QPushButton::clicked, this, &OrderDetail::close);
}

void OrderDetail::populateTable(const vector<QList<QString>>& filteredProducts) {
    this->filteredProducts = filteredProducts;  // Store the member variable
    itemsTable->setRowCount(filteredProducts.size());
    double totalPrice = 0.0;

    for (int row = 0; row < int(filteredProducts.size()); ++row) {
        const QList<QString>& product = filteredProducts[row];

        // Populate each cell in the row
        QTableWidgetItem* nameItem = new QTableWidgetItem(product[0]);
        QTableWidgetItem* quantityItem = new QTableWidgetItem(product[2]);
        QTableWidgetItem* priceItem = new QTableWidgetItem(product[1]);
        QTableWidgetItem* idItem = new QTableWidgetItem(product[3]); // Add Product ID

        itemsTable->setItem(row, 0, nameItem);
        itemsTable->setItem(row, 1, quantityItem);
        itemsTable->setItem(row, 2, priceItem);
        itemsTable->setItem(row, 3, idItem); // Set ID in 4th column

        // Calculate total price
        bool priceOk, quantityOk;
        double price = product[1].toDouble(&priceOk);
        int quantity = product[2].toInt(&quantityOk);
        if (priceOk && quantityOk) {
            totalPrice += price * quantity;
        } else {
            qDebug() << "Invalid data for product:" << product;
        }
    }

    // Update total price label
    totalPriceLabel->setText(QString::number(totalPrice, 'f', 2));
    generateOrderCode(filteredProducts);
}


void OrderDetail::generateOrderCode(const vector<QList<QString>>& filteredProducts) {
    // int randomCode = QRandomGenerator::global()->bounded(1, 1001);  // Generate code between 0001 and 1000
    // orderCode = QString::number(randomCode).rightJustified(4, '0'); // Ensure it's 4 digits
    // orderCodeLabel->setText("OrderNumber: " + orderCode);
    QString filePath = "C:/AllFiles/CODE/C++/Data/orders.txt";
    QFile file(filePath);

    // Open file to read the last used index
    int lastIndex = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString lastLine;
        while (!in.atEnd()) {
            lastLine = in.readLine();
        }

        // Extract last index from the last line
        if (!lastLine.isEmpty()) {
            QStringList fields = lastLine.split(',');
            if (!fields.isEmpty()) {
                lastIndex = fields[0].toInt(); // Get the index from the first column
            }
        }
        file.close();
    }
    int orderIndex = lastIndex + 1;
    orderCodeLabel->setText("OrderNumber: " + QString::number(orderIndex));

    handlePrint(filteredProducts);  // Pass filteredProducts when calling handlePrint
}

#include <QMessageBox> // Include QMessageBox for success notification

void OrderDetail::handlePrint(const vector<QList<QString>>& filteredProducts) {
    QString filePath = "C:/AllFiles/CODE/C++/Data/orders.txt";
    QFile file(filePath);

    // Open file to read the last used index
    int lastIndex = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString lastLine;
        while (!in.atEnd()) {
            lastLine = in.readLine();
        }

        // Extract last index from the last line
        if (!lastLine.isEmpty()) {
            QStringList fields = lastLine.split(',');
            if (!fields.isEmpty()) {
                lastIndex = fields[0].toInt(); // Get the index from the first column
            }
        }
        file.close();
    }

    // Get customer name and check if it's "Unknown"
    QString customerName = customerField->text().isEmpty() ? "Unknown" : customerField->text();
    if (customerName == "Unknown") {
        qDebug() << "Skipping order for unknown customer.";
        return; // Skip the saving process if customer is "Unknown"
    }

    // Increment index for the new order
    int orderIndex = lastIndex + 1;

    // Open file to append the new order
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return;
    }

    QTextStream out(&file);

    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString totalPrice = totalPriceLabel->text();

    QStringList itemsList; // To store "productId,quantity"
    for (const QList<QString>& product : filteredProducts) {
        itemsList.append(QString("%1,%2").arg(product[3]).arg(product[2])); // ID, Quantity
    }

    QString items = itemsList.join(";"); // Join all items with semicolon

    // Write to file in the required format
    out << '\n' << orderIndex << "," // Use dynamically calculated index
        << customerName << ",\""
        << items << "\","
        << totalPrice << ","
        << dateTime;

    file.close();
    QMessageBox::information(this, "Order Saved", "Your order has been successfully saved!");

    // Show success message
    qDebug() << "Order saved to" << filePath;
}
