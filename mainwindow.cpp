#include "mainwindow.h"
#include "productwindow.h"
#include "OrderDetail.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QFile>
#include <QIODevice>
#include <QRegularExpression>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
#include "StatisticWindow.h"
#include <Product.h>
#include <Burger.h>
#include <Drink.h>
#include <HashTable.h>
#include <Order.cpp>
#include <OrderItem.cpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    tableWidget = new QTableWidget(this);  // Initialize tableWidget here
    setupUI();
    setupTable();
    HashTable<Burger> burgerTable;
    HashTable<Drink> drinkTable;
    HashTable<Order> orderTable;
    burgerTable.readFile("C:/AllFiles/CODE/C++/Data/input_burgers.txt");
    drinkTable.readFile("C:/AllFiles/CODE/C++/Data/input_burgers.txt");
    orderTable.readFile("C:/AllFiles/CODE/C++/Data/orders.txt");
    cout << "xxxxxxxxxxx" << orderTable << '\n';
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Search Input and Buttons
    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Search your item...");

    QPushButton* searchButton = new QPushButton("Search", this);
    QPushButton* showAllButton = new QPushButton("Show All", this);  // Show All button

    QPushButton* ascendingButton = new QPushButton("Ascending", this);
    QPushButton* descendingButton = new QPushButton("Descending", this);

    // Connect buttons to slots
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::handleSearch);
    connect(showAllButton, &QPushButton::clicked, this, &MainWindow::handleShowAll);
    connect(ascendingButton, &QPushButton::clicked, this, &MainWindow::sortAscending);
    connect(descendingButton, &QPushButton::clicked, this, &MainWindow::sortDescending);

    // Layout for search input and buttons
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(showAllButton);
    searchLayout->addWidget(ascendingButton);
    searchLayout->addWidget(descendingButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableWidget);

    // Total text browser
    totalTextBrowser = new QTextBrowser(this);
    totalTextBrowser->setFixedHeight(50);
    totalTextBrowser->setPlainText("Total: 0.00");
    mainLayout->addWidget(totalTextBrowser);

    // Product and ORDER buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* productButton = new QPushButton("PRODUCT", this);
    QPushButton* orderButton = new QPushButton("ORDER", this);
    QPushButton* statisticButton = new QPushButton("Statistic", this);
    buttonLayout->addWidget(statisticButton);
    connect(statisticButton, &QPushButton::clicked, this, &MainWindow::openStatisticWindow);

    buttonLayout->addWidget(productButton);
    buttonLayout->addWidget(orderButton);

    mainLayout->addLayout(buttonLayout);

    connect(productButton, &QPushButton::clicked, this, &MainWindow::openProductWindow);
    connect(orderButton, &QPushButton::clicked, this, &MainWindow::openOrderDetail);
}

void MainWindow::openStatisticWindow() {
    // Create the Statistic window
    StatisticWindow* statisticWindow = new StatisticWindow();

    if (statisticWindow) {
        statisticWindow->resize(this->width(), this->height());
        statisticWindow->move(this->pos());
        statisticWindow->show();
        statisticWindow->raise();
        statisticWindow->activateWindow();
    } else {
        qDebug() << "Failed to create StatisticWindow instance";
    }
}


void MainWindow::filterOrdersByDate(const QDateTime& startDate, const QDateTime& endDate, QTableWidget* table) {
    QFile file("C:/AllFiles/C++/Data/orders");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open orders file.";
        return;
    }

    QTextStream in(&file);
    table->setRowCount(0);  // Clear previous results

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",", Qt::SkipEmptyParts);

        if (fields.size() < 6) {
            qDebug() << "Malformed line skipped:" << line;
            continue;
        }

        QString productName = fields[1] + " " + fields[2];  // Combine name and size
        int quantity = fields[3].toInt();
        double price = fields[4].toDouble();
        QString dateTimeStr = fields[5] + " " + fields[6]; // Combine date and time
        QDateTime orderDateTime = QDateTime::fromString(dateTimeStr, "dd/MM/yyyy hh:mm");

        // Filter based on date range
        if (orderDateTime >= startDate && orderDateTime <= endDate) {
            int row = table->rowCount();
            table->insertRow(row);

            // Populate the table with order details
            table->setItem(row, 0, new QTableWidgetItem(productName));
            table->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(price, 'f', 2)));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(quantity * price, 'f', 2)));
            table->setItem(row, 4, new QTableWidgetItem(orderDateTime.toString("dd/MM/yyyy")));
            table->setItem(row, 5, new QTableWidgetItem(orderDateTime.toString("hh:mm")));
        }
    }

    file.close();
}

void MainWindow::setupTable() {
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);
    QStringList headers = {"Name", "Price", "Quantity", "Increment", "Decrement"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Load products from products.txt
    loadFile(R"(C:\AllFiles\CODE\C++\Data\input_burgers.txt)");

    // Load drinks from drinks.txt
    loadFile(R"(C:\AllFiles\CODE\C++\Data\input_drinks.txt)");

    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    updateTotal();
}


void MainWindow::sortAscending() {
    tableWidget->sortItems(1, Qt::AscendingOrder);  // Cột 1 là cột Price
}

void MainWindow::sortDescending() {
    tableWidget->sortItems(1, Qt::DescendingOrder);  // Cột 1 là cột Price
}

void MainWindow::loadFile(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open" << filePath;
        return;
    }

    QTextStream in(&file);
    int row = tableWidget->rowCount();  // Start from the current row count

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() < 5) {
            qDebug() << "Malformed line skipped:" << line;
            continue;
        }

        QString id = fields[0].trimmed();
        QString name = fields[1].trimmed();
        QString description = fields[2].trimmed();
        double price = fields[3].trimmed().toDouble();
        QString size = fields[4].trimmed();

        // Append the size to the name
        QString nameWithSize = QString("%1 (%2)").arg(name).arg(size);

        // Default quantity is 0
        QString quantityStr = "0";

        tableWidget->insertRow(row);

        QTableWidgetItem* nameItem = new QTableWidgetItem(nameWithSize);
        tableWidget->setItem(row, 0, nameItem);

        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        priceItem->setTextAlignment(Qt::AlignRight);
        tableWidget->setItem(row, 1, priceItem);

        QTableWidgetItem* quantityItem = new QTableWidgetItem(quantityStr);
        tableWidget->setItem(row, 2, quantityItem);

        QPushButton* incrementButton = new QPushButton("+");
        incrementButton->setProperty("row", row);
        connect(incrementButton, &QPushButton::clicked, this, &MainWindow::handleIncrement);
        tableWidget->setCellWidget(row, 3, incrementButton);

        QPushButton* decrementButton = new QPushButton("-");
        decrementButton->setProperty("row", row);
        connect(decrementButton, &QPushButton::clicked, this, &MainWindow::handleDecrement);
        tableWidget->setCellWidget(row, 4, decrementButton);

        row++; // Move to the next row
    }

    file.close();
}

QList<QList<QString>> MainWindow::getFilteredProducts() {
    QList<QList<QString>> filteredProducts;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QTableWidgetItem* quantityItem = tableWidget->item(row, 2);
        if (!quantityItem) {
            qDebug() << "Row" << row << "has no quantity item.";
            continue; // Skip rows with missing quantity items
        }

        int quantity = quantityItem->text().toInt();
        qDebug() << "Row" << row << "quantity:" << quantity;

        if (quantity >= 1) {
            QList<QString> productData;
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = tableWidget->item(row, col);
                productData.append(item ? item->text() : "");
            }
            filteredProducts.append(productData);
        }
    }

    qDebug() << "Filtered products:" << filteredProducts;
    return filteredProducts;
}


void MainWindow::handleSearch() {
    QString searchText = searchInput->text().toLower();
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QString name = tableWidget->item(i, 0)->text().toLower();
        if (!name.contains(searchText)) {
            tableWidget->hideRow(i);
        } else {
            tableWidget->showRow(i);
        }
    }
}

void MainWindow::handleShowAll() {
    tableWidget->clear();
    tableWidget->setRowCount(0);
    loadFile(R"(C:\AllFiles\CODE\C++\Data\input_burgers.txt)");
    // Load drinks from drinks.txt
    loadFile(R"(C:\AllFiles\CODE\C++\Data\input_drinks.txt)");
    // for (int i = 0; i < tableWidget->rowCount(); ++i) {
    //     tableWidget->showRow(i);
    // }
    // tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);
    QStringList headers = {"Name", "Price", "Quantity", "Increment", "Decrement"};
    tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::openOrderDetail() {
    QList<QList<QString>> filteredProducts = getFilteredProducts();

    if (filteredProducts.isEmpty()) {
        qDebug() << "No products to display in OrderDetail.";
        return;
    }

    qDebug() << "Filtered products passed to OrderDetail:" << filteredProducts;

    if (orderDetailWindow != nullptr) {
        orderDetailWindow->close();
        delete orderDetailWindow;
        orderDetailWindow = nullptr;
    }

    orderDetailWindow = new OrderDetail(this);
    orderDetailWindow->setAttribute(Qt::WA_DeleteOnClose);
    orderDetailWindow->populateTable(filteredProducts);

    orderDetailWindow->setWindowTitle("Order Details");
    orderDetailWindow->resize(800, 600);
    orderDetailWindow->show();
}


void MainWindow::openProductWindow() {
    qDebug() << "Product button clicked";

    ProductWindow* productWindow = new ProductWindow();
    if (productWindow) {
        productWindow->resize(this->width(), this->height());
        productWindow->move(this->pos());
        productWindow->show();
        productWindow->raise();
        productWindow->activateWindow();
    } else {
        qDebug() << "Failed to create ProductWindow instance";
    }
}

void MainWindow::handleIncrement() {
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int visualRow = tableWidget->indexAt(senderButton->pos()).row(); // Lấy hàng hiển thị hiện tại
        QTableWidgetItem* quantityItem = tableWidget->item(visualRow, 2);
        int currentQuantity = quantityItem ? quantityItem->text().toInt() : 0;

        if (currentQuantity >= 0) {
            updateQuantity(visualRow, 1); // Cập nhật số lượng tại hàng hiển thị
            // saveToFile();
            updateTotal(); // Cập nhật tổng sau khi tăng
        }
    }
}


void MainWindow::handleDecrement() {
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int visualRow = tableWidget->indexAt(senderButton->pos()).row(); // Lấy hàng hiển thị hiện tại
        QTableWidgetItem* quantityItem = tableWidget->item(visualRow, 2);
        int currentQuantity = quantityItem ? quantityItem->text().toInt() : 0;

        if (currentQuantity > 0) {
            updateQuantity(visualRow, -1); // Cập nhật số lượng tại hàng hiển thị
            // saveToFile();
            updateTotal(); // Cập nhật tổng sau khi giảm
        }
    }
}



void MainWindow::updateQuantity(int row, int delta) {
    QTableWidgetItem* quantityItem = tableWidget->item(row, 2);
    if (!quantityItem) {
        qDebug() << "Quantity item not found.";
        return;
    }

    int currentQuantity = quantityItem->text().toInt();
    currentQuantity += delta;
    if (currentQuantity < 0) {
        currentQuantity = 0;
    }

    quantityItem->setText(QString::number(currentQuantity));
}
void MainWindow::updateTotal() {
    double totalSum = 0.0;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        int quantity = tableWidget->item(row, 2)->text().toInt();
        double price = tableWidget->item(row, 1)->text().toDouble();
        totalSum += price * quantity;
    }

    totalTextBrowser->setPlainText(QString("Total: %1").arg(totalSum, 0, 'f', 2));
}

void MainWindow::saveToFile() {
    // QFile file("products.txt");

    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    //     qDebug() << "Failed to open products.txt for writing.";
    //     return;
    // }

    // QTextStream out(&file);

    // for (int row = 0; row < tableWidget->rowCount(); ++row) {
    //     QString name = tableWidget->item(row, 0)->text();
    //     QString price = tableWidget->item(row, 1)->text();
    //     QString quantity = tableWidget->item(row, 2)->text();

    //     // Create CSV-like format:
    //     // ID,Name,Description,Price,Category,Availability
    //     // For simplicity, we'll generate dummy data for ID and Description
    //     // Category can be determined from the price or other criteria if needed
    //     int id = row + 1; // Generate a simple ID (can be replaced with actual ID logic)
    //     QString description = "Description for " + name;
    //     QString category = "Beef"; // Or derive based on product name or other logic
    //     bool isAvailable = true; // Assume products are available by default

    //     out << id << ","
    //         << name << ","
    //         << description << ","
    //         << price << ","
    //         << category << ","
    //         << (isAvailable ? "true" : "false") << "\n";
    // }

    // file.close();
}

