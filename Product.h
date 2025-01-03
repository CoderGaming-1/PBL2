#ifndef Product_h
#define Product_h

#include <iostream>
#include <string>
using namespace std;

class Product
{
protected:
    int product_id;
    string name;
    string description;
    // double price;

public:
    Product(int id = 0, const string &name = "", const string &desc = "");

    // Getters
    int getId() const;
    string getName() const;
    string getDescription() const;
    // double getPrice() const;

    // Setters
    void setId(int id);
    void setName(const string &name);
    void setDescription(const string &desc);
    // void setPrice(double price);

    virtual double getPrice() const = 0;

    // Operator Overloads
    bool operator==(const Product &other) const;
    friend istream &operator>>(istream &is, Product &product);
    friend ostream &operator<<(ostream &os, const Product &product);

};

#endif
