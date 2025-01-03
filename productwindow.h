#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <Product.h>
#include <Burger.h>
#include <Drink.h>
#include <HashTable.h>


class ProductWindow : public QWidget {
    Q_OBJECT

public:
    explicit ProductWindow(QWidget *parent = nullptr);
    ~ProductWindow() override;
    HashTable<Burger>& getBurgerTable();
    HashTable<Drink>& getDrinkTable();

private slots:
    void handleUpdate(int row);
    void handleDelete(int row);
    void handleAdd();
    void handleSearch(const QString &searchText);
    void handleShowAll();
    void saveProductsToFile();
    void loadProductsFromFile();  // Make sure this function is declared
    void reconnectButtons();

private:
    // HashTable<Product> productTableHash;
    HashTable<Burger> burgerTable;
    HashTable<Drink> drinkTable;
    QTableWidget *productTable;
    QString getProductType() const;
    // Product data
    QStringList productIds;         // Store product IDs
    QStringList productNames;       // Store product names
    QStringList productDescriptions; // Store product descriptions
    QList<double> productPrices;    // Store product prices
    QStringList productSizes;       // Store product sizes
    QStringList productTypes;
};

#endif // PRODUCTWINDOW_H
