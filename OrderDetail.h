#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include <vector>
using namespace std;

class OrderDetail : public QMainWindow {
    Q_OBJECT

public:
    explicit OrderDetail(QWidget* parent = nullptr);
    ~OrderDetail();

    void populateTable(const vector<QList<QString>>& filteredProducts);
    void handlePrint(const vector<QList<QString>>& filteredProducts);
    void generateOrderCode(const vector<QList<QString>>& filteredProducts);
    void clicked(bool checked);

private:
    void setupUI();
    void loadDataFromFile(); // Declaration for the function to load data from the file
    QLineEdit* customerField;
    vector<QList<QString>> filteredProducts;
    QString orderCode;
    QLabel* orderCodeLabel;
    QLabel* totalPriceLabel;
    QTableWidget* itemsTable;
    QLineEdit* nameClientLineEdit; // Input field for client name
};

#endif // ORDERDETAIL_H
