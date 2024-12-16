#include "productdetail.h"
#include "productwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDebug>
#include <QHeaderView> // Include this for QHeaderView
#include <QLineEdit>   // Include QLineEdit for the search input
#include "addproductdialog.h" // Include AddProductDialog
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDateTime>

ProductWindow::~ProductWindow() {
    qDebug() << "ProductWindow destructor called";
}
void ProductWindow::handleDelete(int row) {
    qDebug() << "Delete button clicked for row:" << row;
    if (row >= 0 && row < productTable->rowCount()) {
        productTable->removeRow(row);  // Remove the row from the table

        // Remove the product from the lists
        productNames.removeAt(row);
        productPrices.removeAt(row);

        // Save the updated products to file
        saveProductsToFile();
    }

    // After removing a row, reset connections for the remaining "Update" and "Delete" buttons
    for (int i = 0; i < productTable->rowCount(); ++i) {
        QPushButton *updateButton = qobject_cast<QPushButton*>(productTable->cellWidget(i, 2)->layout()->itemAt(0)->widget());
        QPushButton *deleteButton = qobject_cast<QPushButton*>(productTable->cellWidget(i, 2)->layout()->itemAt(1)->widget());

        // Reconnect update button to the correct row
        connect(updateButton, &QPushButton::clicked, this, [=]() {
            handleUpdate(i);  // Pass the new row index to handleUpdate
        });

        // Reconnect delete button to the correct row
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            handleDelete(i);  // Pass the new row index to handleDelete
        });
    }
}

void ProductWindow::handleUpdate(int row) {
    qDebug() << "Update button clicked for row:" << row;
    if (row >= 0 && row < productTable->rowCount()) {
        QString name = productTable->item(row, 0)->text();
        double price = productTable->item(row, 1)->text().toDouble();

        // Open ProductDetailDialog window
        ProductDetailDialog *detailDialog = new ProductDetailDialog(name, price, this);

        // Show the dialog and process user input
        if (detailDialog->exec() == QDialog::Accepted) {
            // Get updated values and apply them
            QString updatedName = detailDialog->getUpdatedName();
            double updatedPrice = detailDialog->getUpdatedPrice();

            // Update the table with the new values
            productTable->item(row, 0)->setText(updatedName);
            productTable->item(row, 1)->setText(QString::number(updatedPrice));

            // Update the data in the list
            productNames[row] = updatedName;
            productPrices[row] = updatedPrice;

            // Save the updated products to file
            saveProductsToFile();
        }

        detailDialog->deleteLater();
    } else {
        qDebug() << "Invalid row index";
    }
}

void ProductWindow::saveProductsToFile() {
    QFile file("C:/AllFiles/CODE/C++/Data/input_burgers.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open products.txt for writing";
        return;
    }

    QTextStream out(&file);
    QString currentDateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss"); // Get the current date and time

    for (int i = 0; i < productNames.size(); ++i) {
        out << QString("{\"%1\" %2 %3}\n")  // Add the current timestamp
                   .arg(productNames[i].replace("\"", "\\\""))  // Escape quotes in names
                   .arg(productPrices[i])
                   .arg(currentDateTime);  // Insert the real-time date and time
    }

    file.close();
}

void ProductWindow::loadProductsFromFile() {
    QFile fileBurgers("C:/AllFiles/CODE/C++/Data/input_burgers.txt");
    QFile fileDrinks("C:/AllFiles/CODE/C++/Data/input_drinks.txt");

    productNames.clear();
    productPrices.clear();
    productTypes.clear();  // Khởi tạo một list mới để chứa loại sản phẩm

    // Load burger data
    if (!fileBurgers.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open input_burgers.txt";
    } else {
        QTextStream inBurgers(&fileBurgers);
        while (!inBurgers.atEnd()) {
            QString line = inBurgers.readLine();
            QStringList fields = line.split(",", Qt::SkipEmptyParts);

            if (fields.size() >= 6) {  // Đảm bảo có đủ 6 trường dữ liệu
                QString id = fields[0].trimmed();
                QString name = fields[1].trimmed();
                QString description = fields[2].trimmed();
                double price = fields[3].trimmed().toDouble();
                QString Type = fields[4].trimmed();
                QString size = fields[5].trimmed();

                // Lưu thông tin vào các danh sách
                productIds.append(id);
                productNames.append(name);
                productDescriptions.append(description);
                productPrices.append(price);
                productSizes.append(size);
                productTypes.append(Type);  // Lưu loại "Beef" hoặc "Non-Beef"
            }
        }
        fileBurgers.close();
    }

    // Load drink data
    if (!fileDrinks.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open input_drinks.txt";
    } else {
        QTextStream inDrinks(&fileDrinks);
        while (!inDrinks.atEnd()) {
            QString line = inDrinks.readLine();
            QStringList fields = line.split(",", Qt::SkipEmptyParts);

            if (fields.size() >= 5) {  // Đảm bảo có đủ 5 trường dữ liệu
                QString id = fields[0].trimmed();
                QString name = fields[1].trimmed();
                QString description = fields[2].trimmed();
                double price = fields[3].trimmed().toDouble();
                QString size = fields[4].trimmed();

                // Lưu thông tin vào các danh sách
                productIds.append(id);
                productNames.append(name);
                productDescriptions.append(description);
                productPrices.append(price);
                productSizes.append(size);
                productTypes.append(size);  // Lưu loại là "Small" hoặc các loại khác
            }
        }
        fileDrinks.close();
    }

    // Cập nhật bảng
    productTable->setRowCount(productNames.size());
    for (int i = 0; i < productNames.size(); ++i) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(productNames[i]);
        QTableWidgetItem *typeItem = new QTableWidgetItem(productDescriptions[i]);  // Cập nhật với Type
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(productPrices[i]));

        productTable->setItem(i, 0, nameItem);
        productTable->setItem(i, 1, typeItem);  // Thêm Type vào cột thứ 2
        productTable->setItem(i, 2, priceItem);

        QWidget *actionWidget = new QWidget(this);
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        QPushButton *updateButton = new QPushButton("Update", this);
        QPushButton *deleteButton = new QPushButton("Delete", this);
        actionLayout->addWidget(updateButton);
        actionLayout->addWidget(deleteButton);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        actionLayout->setSpacing(5);
        productTable->setCellWidget(i, 3, actionWidget);  // Chỉnh lại cột Action

        // Kết nối các nút
        connect(updateButton, &QPushButton::clicked, this, [=]() {
            handleUpdate(i);
        });
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            handleDelete(i);
        });
    }
}




void ProductWindow::reconnectButtons() {
    for (int i = 0; i < productTable->rowCount(); ++i) {
        QWidget *actionWidget = productTable->cellWidget(i, 2);
        QHBoxLayout *actionLayout = qobject_cast<QHBoxLayout*>(actionWidget->layout());
        if (!actionLayout) continue;

        QPushButton *updateButton = qobject_cast<QPushButton*>(actionLayout->itemAt(0)->widget());
        QPushButton *deleteButton = qobject_cast<QPushButton*>(actionLayout->itemAt(1)->widget());

        if (updateButton && deleteButton) {
            disconnect(updateButton, nullptr, nullptr, nullptr);
            disconnect(deleteButton, nullptr, nullptr, nullptr);

            connect(updateButton, &QPushButton::clicked, this, [=]() {
                handleUpdate(i);
            });
            connect(deleteButton, &QPushButton::clicked, this, [=]() {
                handleDelete(i);
            });
        }
    }
}



// Constructor
ProductWindow::ProductWindow(QWidget *parent) : QWidget(parent), productTable(new QTableWidget(this)) {

    setWindowTitle("Product Window");

    loadProductsFromFile();
    // Initialize product data
    // if (productNames.isEmpty()) {
    //     productNames = { "Classic beef burger", "Crispy golden fries", "Refreshing cola" };
    //     productPrices = { 10.0, 20.0, 15.5 };
    // }

    productTable->setRowCount(productNames.size());
    productTable->setColumnCount(4);  // Thêm một cột cho Type
    productTable->setHorizontalHeaderLabels({"Name", "Type", "Price", "Action"});
    productTable->horizontalHeader()->setStretchLastSection(true);
    productTable->verticalHeader()->setVisible(false);

    // Search Input and Buttons
    QLineEdit *searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Search your item...");
    QPushButton *searchButton = new QPushButton("Search", this);
    QPushButton *showAllButton = new QPushButton("Show All", this);  // "Show All" button

    // Connect the Search button
    connect(searchButton, &QPushButton::clicked, this, [=]() {
        handleSearch(searchInput->text());
    });

    // Connect the Show All button
    connect(showAllButton, &QPushButton::clicked, this, [=]() {
        handleShowAll();
    });

    // Search Layout
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(showAllButton);  // Add "Show All" button to the layout

    for (int i = 0; i < productNames.size(); ++i) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(productNames[i]);
        QTableWidgetItem *typeItem = new QTableWidgetItem(productTypes[i]);
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(productPrices[i]));
        productTable->setItem(i, 0, nameItem);
        productTable->setItem(i, 1, typeItem);
        productTable->setItem(i, 2, priceItem);

        QWidget *actionWidget = new QWidget(this);
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        QPushButton *updateButton = new QPushButton("Update", this);
        QPushButton *deleteButton = new QPushButton("Delete", this);
        actionLayout->addWidget(updateButton);
        actionLayout->addWidget(deleteButton);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        actionLayout->setSpacing(5);
        productTable->setCellWidget(i, 3, actionWidget);

        // Connect buttons to their respective slots with row index
        connect(updateButton, &QPushButton::clicked, this, [=]() {
            handleUpdate(i);  // Pass the row index to handleUpdate
        });
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            handleDelete(i);  // Handle delete, passing the row index
        });
    }

    // Bottom layout for Add and Back buttons
    QPushButton *addButton = new QPushButton("Add", this);
    QPushButton *backButton = new QPushButton("Back", this);
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(addButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(backButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(searchLayout);  // Add search layout to the main layout
    mainLayout->addWidget(productTable);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &ProductWindow::handleAdd);

    // Close the current window when the Back button is clicked
    connect(backButton, &QPushButton::clicked, this, &ProductWindow::close);
}
void ProductWindow::handleShowAll() {
    for (int i = 0; i < productTable->rowCount(); ++i) {
        productTable->showRow(i);  // Show all rows
    }
}

// Slot to handle Add button
// Slot to handle Add button
void ProductWindow::handleAdd() {
    AddProductDialog *addDialog = new AddProductDialog(this);

    // Show the dialog and process user input
    if (addDialog->exec() == QDialog::Accepted) {
        QString newName = addDialog->getProductName();
        double newPrice = addDialog->getProductPrice();

        // Add the new product to the lists
        productNames.append(newName);
        productPrices.append(newPrice);

        // Add the new product to the table
        int row = productTable->rowCount();
        productTable->insertRow(row);  // Insert a new row

        productTable->setItem(row, 0, new QTableWidgetItem(newName));
        productTable->setItem(row, 1, new QTableWidgetItem(QString::number(newPrice)));

        QWidget *actionWidget = new QWidget(this);
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
        QPushButton *updateButton = new QPushButton("Update", this);
        QPushButton *deleteButton = new QPushButton("Delete", this);
        actionLayout->addWidget(updateButton);
        actionLayout->addWidget(deleteButton);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        actionLayout->setSpacing(5);
        productTable->setCellWidget(row, 2, actionWidget);

        // Reconnect buttons after adding new row
        connect(updateButton, &QPushButton::clicked, this, [=]() {
            handleUpdate(row);  // Pass the new row index to handleUpdate
        });
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            handleDelete(row);  // Handle delete for the new row
        });

        // Save the new product to the file
        saveProductsToFile();
    }

    addDialog->deleteLater();

    // Reload the products from file to ensure it's up-to-date
    // loadProductsFromFile();
}


// Slot to handle search
void ProductWindow::handleSearch(const QString &searchText) {
    // Filter products based on the search text
    for (int i = 0; i < productNames.size(); ++i) {
        QString name = productNames[i].toLower();
        if (name.contains(searchText.toLower())) {
            // If the product name matches the search, show it
            productTable->showRow(i);
        } else {
            // If it doesn't match, hide the row
            productTable->hideRow(i);
        }
    }
}



