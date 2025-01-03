#include "Drink.h"
#include <iostream>
using namespace std;

// Constructor
Drink::Drink(int id, const string &name, const string &desc, double price,
             const string &size)
    : Product(id, name, desc), price(price), size(size) {}

// Getters
string Drink::getSize() const
{
    return size;
}

double Drink::getPrice() const
{
    return price;
}

// Setters
void Drink::setSize(const string &size)
{
    this->size = size;
}

void Drink::setPrice(double price)
{
    this->price = price;
}

istream& operator>>(istream& is, Drink& drink) {
    string productIdStr;

    getline(is, productIdStr, ',');
    getline(is, drink.name, ',');
    getline(is, drink.description, ',');
    is >> drink.price;
    is.ignore();
    getline(is, drink.size);

    drink.product_id = stoi(productIdStr);
    return is;
}


ostream &operator<<(ostream &os, const Drink &drink) {
    os << drink.product_id << "," << drink.name << "," << drink.description << ","
       << drink.price << "," << drink.size;
    return os;
}
