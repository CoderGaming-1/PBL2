#ifndef PRODUCTDETAIL_H
#define PRODUCTDETAIL_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ProductDetailDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProductDetailDialog(const QString &name, double price, QWidget *parent = nullptr);
    QString getUpdatedName() const;
    double getUpdatedPrice() const;

private:
    QLineEdit *nameEdit;
    QLineEdit *priceEdit;
};

#endif // PRODUCTDETAIL_H
