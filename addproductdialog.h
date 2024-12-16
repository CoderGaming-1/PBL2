#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox> // Add QComboBox here
#include <QCheckBox>

class AddProductDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = nullptr);

    QString getProductName() const;
    QString getProductDescription() const;
    double getProductPrice() const;
    QString getProductType() const;
    bool isSpicy() const;  // For burgers

private slots:
    void onProductTypeChanged(const QString &type);
    void saveToFile();

private:
    QLineEdit *nameEdit;
    QLineEdit *descriptionEdit;
    QDoubleSpinBox *priceSpinBox;
    QComboBox *typeComboBox;  // Changed to QComboBox
    QCheckBox *spicyCheckBox; // For burgers
    QComboBox *productCategoryComboBox; // To select Drink or Burger

    QPushButton *addButton;
};

#endif // ADDPRODUCTDIALOG_H
