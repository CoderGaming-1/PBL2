#include "productdetail.h"

ProductDetailDialog::ProductDetailDialog(const QString &name, double price, QWidget *parent)
    : QDialog(parent) {

    // Set the dialog title
    setWindowTitle("Edit Product");

    // Create labels and text fields
    QLabel *nameLabel = new QLabel("Name:", this);
    nameEdit = new QLineEdit(name, this);

    QLabel *priceLabel = new QLabel("Price:", this);
    priceEdit = new QLineEdit(QString::number(price), this);

    // Create Save and Cancel buttons
    QPushButton *saveButton = new QPushButton("Save", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);

    QHBoxLayout *priceLayout = new QHBoxLayout();
    priceLayout->addWidget(priceLabel);
    priceLayout->addWidget(priceEdit);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(priceLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);

    // Connect buttons to slots
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);  // Accept dialog (save)
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);  // Reject dialog (cancel)
}

QString ProductDetailDialog::getUpdatedName() const {
    return nameEdit->text();
}

double ProductDetailDialog::getUpdatedPrice() const {
    return priceEdit->text().toDouble();
}
