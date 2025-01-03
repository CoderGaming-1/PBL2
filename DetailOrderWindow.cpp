#include "DetailOrderWindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QTextEdit>

DetailOrderWindow::DetailOrderWindow(const Order_2& order, QWidget* parent)
    : QDialog(parent), order(order)  // Initialize 'order' in the initializer list
{
    // Set up the UI for showing the order details (you can use labels or other widgets)
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Order ID: " + order.orderId));
    layout->addWidget(new QLabel("Client Name: " + order.customerName));
    layout->addWidget(new QLabel("Date: " + order.datetime.toString("dd/MM/yyyy HH:mm")));

    // Add a title for the product details section
    QLabel* productsTitleLabel = new QLabel("Products:", this);
    layout->addWidget(productsTitleLabel);

    // Create a QTextEdit to display the product details, allowing custom formatting
    QTextEdit* productDetailsTextEdit = new QTextEdit(this);
    productDetailsTextEdit->setReadOnly(true);  // Make it read-only so the user can't edit the text
    productDetailsTextEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // Split the products into lines and underline them
    // QStringList productList = order.items.split(";"); // Assuming the products are separated by semicolons
    QStringList productList;
    QString formattedProductDetails;

    for (const QString& product : productList) {
        formattedProductDetails += "<u>" + product.trimmed() + "</u><br>";  // Underline each product and add line break
    }

    // Set the formatted product details as the text in QTextEdit
    productDetailsTextEdit->setHtml(formattedProductDetails);

    // Add the QTextEdit to the layout
    layout->addWidget(productDetailsTextEdit);

    // Set the dialog layout
    setLayout(layout);
    setWindowTitle("Order Details");
    setFixedSize(300, 300);  // Adjusted the fixed size for a better view
}
