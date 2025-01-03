#ifndef Drink_h
#define Drink_h

#include "Product.h"

class Drink : public Product
{
private:
    string size; // e.g., Small, Medium, Large
    double price;

public:
    // Constructor
    Drink(int id = 0, const string &name = "", const string &desc = "", double price = 0.0,
          const string &size = "");

    // Getters
    string getSize() const;
    double getPrice() const;

    // Setters
    void setSize(const string &size);
    void setPrice(double price);

    friend istream &operator>>(istream &is, Drink &drink);
    friend ostream &operator<<(ostream &os, const Drink &drink);
};

#endif
