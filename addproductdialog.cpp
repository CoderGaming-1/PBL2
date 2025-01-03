#include "addproductdialog.h"
#include "Burger.h"
#include "Drink.h"
#include "productwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AddProductDialog::AddProductDialog(ProductWindow &productWindow, QWidget *parent)
    : QDialog(parent) {
    // Set up UI components
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *categoryLabel = new QLabel("Select Product Category:");
    productCategoryComboBox = new QComboBox();
    productCategoryComboBox->addItems({"Drink", "Burger"});
    layout->addWidget(categoryLabel);
    layout->addWidget(productCategoryComboBox);

    QLabel *nameLabel = new QLabel("Name:");
    nameEdit = new QLineEdit();
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    descriptionEdit = new QLineEdit();
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *priceLabel = new QLabel("Price:");
    priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setRange(0.01, 9999.99);
    layout->addWidget(priceLabel);
    layout->addWidget(priceSpinBox);

    QLabel *typeLabel = new QLabel("Type:");
    typeComboBox = new QComboBox();  // Use QComboBox for type
    layout->addWidget(typeLabel);
    layout->addWidget(typeComboBox);

    spicyCheckBox = new QCheckBox("Spicy");
    layout->addWidget(spicyCheckBox);

    addButton = new QPushButton("Add");
    layout->addWidget(addButton);

    setLayout(layout);

    // Initially hide spicy checkbox
    spicyCheckBox->hide();

    // Connect signals
    connect(productCategoryComboBox, &QComboBox::currentTextChanged,
            this, &AddProductDialog::onProductTypeChanged);
    connect(addButton, &QPushButton::clicked, this, [this, &productWindow]() {
        saveToFile(productWindow);
    });


    // Populate the type combo box when the dialog is first opened
    onProductTypeChanged(productCategoryComboBox->currentText());
}


QString AddProductDialog::getProductName() const {
    return nameEdit->text();
}

QString AddProductDialog::getProductDescription() const {
    return descriptionEdit->text();
}

double AddProductDialog::getProductPrice() const {
    return priceSpinBox->value();
}

QString AddProductDialog::getProductType() const {
    return typeComboBox->currentText();  // Use QComboBox to get selected type
}

bool AddProductDialog::isSpicy() const {
    return spicyCheckBox->isChecked();
}

void AddProductDialog::onProductTypeChanged(const QString &type) {
    // Clear existing type options
    typeComboBox->clear();

    // Update type options based on selected category
    if (type == "Drink") {
        typeComboBox->addItems({"Small", "Medium", "Large"}); // Options for drinks
        spicyCheckBox->hide();
    } else if (type == "Burger") {
        typeComboBox->addItems({"Beef", "Chicken", "Pig"}); // Options for burgers
        spicyCheckBox->show();  // Show spicy checkbox for burgers
    }
}

void AddProductDialog::saveToFile(ProductWindow &productWindow) {
    QString category = productCategoryComboBox->currentText();
    QString name = getProductName();
    QString description = getProductDescription();
    double price = getProductPrice();
    QString type = getProductType();
    QString filePath;

    if (category == "Drink") {
        filePath = "C:\\AllFiles\\CODE\\C++\\Data\\input_drinks.txt";
    } else if (category == "Burger") {
        filePath = "C:\\AllFiles\\CODE\\C++\\Data\\input_burgers.txt";
    }

    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream inOut(&file);

        // Find the last ID in the file
        QString lastLine;
        while (!inOut.atEnd()) {
            lastLine = inOut.readLine();
        }

        int id = 1; // Default starting ID if the file is empty
        if (!lastLine.isEmpty()) {
            QStringList parts = lastLine.split(",");
            if (!parts.isEmpty()) {
                id = parts[0].toInt() + 1; // Increment the last ID
            }
        }

        // Move to the end of the file to append
        file.seek(file.size());
        QTextStream out(&file);

        if (category == "Drink") {
            Drink newDrink(id, name.toStdString(), description.toStdString(), price, type.toStdString());
            HashTable<Drink> &table = productWindow.getDrinkTable();
            table.readFile(filePath.toStdString());
            table.add(newDrink);
            out << '\n' << id << "," << name << "," << description << "," << price << "," << type;
        } else if (category == "Burger") {
            Burger newBurger(id, name.toStdString(), description.toStdString(), price, type.toStdString(), isSpicy() ? true : false);
            HashTable<Burger> &table = productWindow.getBurgerTable();
            table.readFile(filePath.toStdString());
            table.add(newBurger);
            cout << "asdofijaosifd" << '\n';
            cout << table << '\n';
            out << '\n' << id << "," << name << "," << description << "," << price << "," << type << "," << (isSpicy() ? "true" : "false");
        }

        file.close();
        QMessageBox::information(this, "Success", "Product added successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Unable to open file for writing.");
    }
}
