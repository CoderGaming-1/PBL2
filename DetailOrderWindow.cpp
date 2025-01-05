#include "DetailOrderWindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>
#include <QTextEdit>
#include <HashTable.cpp>
#include <Order.h>
#include <Burger.h>
#include <Drink.h>
#include <Array.cpp>
#include <OrderItem.h>

DetailOrderWindow::DetailOrderWindow(const Order_2& order, QWidget* parent)
    : QDialog(parent), order(order)  // Initialize 'order' in the initializer list
{
    // Set up the UI for showing the order details (you can use labels or other widgets)
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Order ID: " + order.orderId));
    layout->addWidget(new QLabel("Client Name: " + order.customerName));
    layout->addWidget(new QLabel("Date: " + order.datetime.toString("dd/MM/yyyy HH:mm")));

    HashTable<Order> orderTable;
    HashTable<Burger> burgerTable1;
    HashTable<Drink> drinkTable1;
    orderTable.readFile("C:/AllFiles/Code/C++/Data/orders.txt");
    burgerTable1.readFile("C:/AllFiles/CODE/C++/Data/input_burgers.txt");
    drinkTable1.readFile("C:/AllFiles/CODE/C++/Data/input_drinks.txt");
    // cout << "qqqqqqqqqqqqqqqq" << orderTable[1] << '\n';
    const Order* orderPtr = orderTable[order.orderId.toInt()];

    const Order& norder = *orderPtr; // Dereference the pointer
    // cout << "Order details: " << norder << '\n';
    // cout << norder.getItems() << '\n';

    // for (int i = 0; i < norder.getItems().size; i++)
    // {
    //     cout << norder.getItems().items[i] << '\n';
    // }
    // cout << norder.getItems().get(0)->getId() << '\n';
    // cout << norder.getItems().get(0)->getQuantity() << '\n';

    // Add a title for the product details section
    // QLabel* productsTitleLabel = new QLabel("Products:", this);
    // layout->addWidget(productsTitleLabel);

    QTableWidget* productsTable = new QTableWidget(this);
    productsTable->setColumnCount(2);
    productsTable->setHorizontalHeaderLabels({"Product Name", "Quantity"});
    productsTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make the table read-only
    productsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < norder.getItems().size; i++) {
        const OrderItem* item = norder.getItems().get(i); // Assuming get(i) returns a pointer
        int productId = item->getId();
        int quantity = item->getQuantity();

        QString productName;

        // Look up product name in burgerTable or drinkTable
        if (productId <= 200) {
            productName = QString::fromStdString(burgerTable1[productId]->getName());
        } else {
            productName = QString::fromStdString(drinkTable1[productId]->getName());
        }

        // Add a new row to the table
        int row = productsTable->rowCount();
        productsTable->insertRow(row);
        productsTable->setItem(row, 0, new QTableWidgetItem(productName));
        productsTable->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
    }

    // Add the products table to the layout
    layout->addWidget(new QLabel("Products:"));
    layout->addWidget(productsTable);

    // Set dialog properties
    setLayout(layout);
    setWindowTitle("Order Details");
    resize(400, 300); // Adjust the size of the dialog

    // // Create a QTextEdit to display the product details, allowing custom formatting
    // QTextEdit* productDetailsTextEdit = new QTextEdit(this);
    // productDetailsTextEdit->setReadOnly(true);
    // productDetailsTextEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // // Split the products into lines and underline them
    // // QStringList productList = order.items.split(";"); // Assuming the products are separated by semicolons
    // QStringList productList;
    // QString formattedProductDetails;

    // for (const QString& product : productList) {
    //     formattedProductDetails += "<u>" + product.trimmed() + "</u><br>";  // Underline each product and add line break
    // }

    // // Set the formatted product details as the text in QTextEdit
    // productDetailsTextEdit->setHtml(formattedProductDetails);

    // // Add the QTextEdit to the layout
    // layout->addWidget(productDetailsTextEdit);

    // // Set the dialog layout
    // setLayout(layout);
    // setWindowTitle("Order Details");
    // setFixedSize(300, 300);  // Adjusted the fixed size for a better view
}
