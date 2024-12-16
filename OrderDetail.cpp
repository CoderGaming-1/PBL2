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
    itemsTable->setColumnCount(3);
    QStringList headers = {"Item Name", "Quantity", "Price"};
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

void OrderDetail::populateTable(const QList<QList<QString>>& filteredProducts) {
    this->filteredProducts = filteredProducts;  // Store it in the member variable
    itemsTable->setRowCount(filteredProducts.size());
    double totalPrice = 0.0;

    for (int row = 0; row < filteredProducts.size(); ++row) {
        const QList<QString>& product = filteredProducts[row];

        QTableWidgetItem* nameItem = new QTableWidgetItem(product[0]);
        QTableWidgetItem* quantityItem = new QTableWidgetItem(product[2]);
        QTableWidgetItem* priceItem = new QTableWidgetItem(product[1]);

        itemsTable->setItem(row, 0, nameItem);
        itemsTable->setItem(row, 1, quantityItem);
        itemsTable->setItem(row, 2, priceItem);

        // Convert price and quantity to double and calculate item total
        double price = product[1].toDouble();
        int quantity = product[2].toInt();
        totalPrice += price * quantity; // Accumulate the total price
    }

    // Update total price label
    totalPriceLabel->setText(QString::number(totalPrice, 'f', 2));
    generateOrderCode(filteredProducts);
}


void OrderDetail::generateOrderCode(const QList<QList<QString>>& filteredProducts) {
    int randomCode = QRandomGenerator::global()->bounded(1, 1001);  // Generate code between 0001 and 1000
    orderCode = QString::number(randomCode).rightJustified(4, '0'); // Ensure it's 4 digits
    orderCodeLabel->setText("OrderNumber: " + orderCode);

    handlePrint(filteredProducts);  // Pass filteredProducts when calling handlePrint
}

void OrderDetail::handlePrint(const QList<QList<QString>>& filteredProducts) {
    QString filePath = "C:/AllFiles/CODE/C++/Data/orders.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return;
    }

    QTextStream out(&file);
    QString dateTime = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");

    QString customerName = customerField->text().isEmpty() ? "Unknown" : customerField->text();
    QString totalPrice = totalPriceLabel->text();

    // Initialize the item details string
    QString itemDetails;

    // Loop through filteredProducts and build the item details string
    if (filteredProducts.size() > 1) {
        QStringList itemsList;  // To store individual item details
        for (const QList<QString>& product : filteredProducts) {
            // Check if the type (product[3]) is empty, and exclude the parentheses if it is
            QString itemDetail;
            if (product[3].isEmpty()) {
                itemDetail = QString("%1 %2").arg(product[0]).arg(product[2]); // Name Quantity
            } else {
                itemDetail = QString("%1 (%2) %3").arg(product[0]).arg(product[3]).arg(product[2]); // Name (Type) Quantity
            }
            itemsList.append(itemDetail);
        }
        itemDetails = itemsList.join(" ; "); // Join all items with a semicolon and space
    } else {
        const QList<QString>& product = filteredProducts.first();
        // Check if the type (product[3]) is empty, and exclude the parentheses if it is
        if (product[3].isEmpty()) {
            itemDetails = QString("%1 %2").arg(product[0]).arg(product[2]); // Name Quantity
        } else {
            itemDetails = QString("%1 (%2) %3").arg(product[0]).arg(product[3]).arg(product[2]); // Name (Type) Quantity
        }
    }

    // Write the order details into the file
    out << orderCode << " "
        << customerName << " "
        << totalPrice << " "
        << dateTime << " "
        << itemDetails << "\n";

    file.close();
    qDebug() << "Order saved to" << filePath;
}
