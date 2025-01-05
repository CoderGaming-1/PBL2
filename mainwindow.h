#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <vector>
using namespace std;

// Forward declarations for custom windows
class OrderDetail;
class ProductWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void filterOrdersByDate(const QDateTime& startDate, const QDateTime& endDate, QTableWidget* table);
private:
    QStringList productIds;
    OrderDetail* orderDetailWindow;
    QTableWidget* tableWidget;
    QTextBrowser* totalTextBrowser;
    QLineEdit* searchInput;
    vector<QList<QString>> getFilteredProducts();
    void setupUI();
    void setupTable();
    void updateQuantity(int row, int delta);
    void updateTotal();
    void loadFile(const QString& filePath);
    void updateStatisticTable(const QList<QString>& filteredOrders);  // This can be used later to populate the statistic table
    void sortAscending();
    void sortDescending();

private slots:
     void openStatisticWindow();  // Add this line
    void handleIncrement();
    void handleDecrement();

    void openProductWindow();
    void handleSearch();
    void handleShowAll();
    void openOrderDetail();
    void saveToFile();
};

#endif // MAINWINDOW_H
