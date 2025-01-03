#include "Burger.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
Burger::Burger(int id, const string &name, const string &desc, double price,
               const string &pattyType, bool isSpicy)
    : Product(id, name, desc), price(price), pattyType(pattyType), isSpicy(isSpicy) {}

// Getters
string Burger::getPattyType() const
{
    return pattyType;
}

bool Burger::getIsSpicy() const
{
    return isSpicy;
}

double Burger::getPrice() const
{
    return price;
}

// Setters
void Burger::setPattyType(const string &type)
{
    pattyType = type;
}

void Burger::setIsSpicy(bool spicy)
{
    isSpicy = spicy;
}

void Burger::setPrice(double price)
{
    this->price = price;
}

istream& operator>>(istream& is, Burger& burger) {
    string productIdStr;
    string isSpicyStr;

    getline(is, productIdStr, ',');
    getline(is, burger.name, ',');
    getline(is, burger.description, ',');
    is >> burger.price;
    is.ignore();
    getline(is, burger.pattyType, ',');
    getline(is, isSpicyStr);
    burger.product_id = stoi(productIdStr);
    burger.isSpicy = (isSpicyStr == "true");
    return is;
}

// istream& operator>>(istream& is, Burger& burger) {
//     string productIdStr;
//     string isSpicyStr;

//     getline(is, productIdStr, ',');
//     getline(is, burger.name, ',');
//     getline(is, burger.description, ',');
//     is >> burger.price;
//     is.ignore();
//     getline(is, burger.pattyType, ',');
//     getline(is, isSpicyStr);

//     burger.product_id = stoi(productIdStr);
//     burger.isSpicy = (isSpicyStr == "1");
//     return is;
// }

ostream &operator<<(ostream &os, const Burger &burger) {
    os << burger.product_id << "," << burger.name << "," << burger.description << ","
       << burger.price << "," << burger.pattyType << "," << (burger.isSpicy ? "true" : "false");
    return os;
}
