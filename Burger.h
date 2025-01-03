#ifndef Burger_h
#define Burger_h

#include "Product.h"

class Burger : public Product
{
private:
    string pattyType;
    bool isSpicy;
    double price;

public:
    // Constructor
    Burger(int id = 0, const string &name = "", const string &desc = "", double price = 0.0,
           const string &pattyType = "", bool isSpicy = false);

    // Getters
    string getPattyType() const;
    bool getIsSpicy() const;
    double getPrice() const;

    // Setters
    void setPattyType(const string &type);
    void setIsSpicy(bool spicy);
    void setPrice(double price);

    friend istream &operator>>(istream &is, Burger &burger);
    friend ostream &operator<<(ostream &os, const Burger &burger);
};

#endif
