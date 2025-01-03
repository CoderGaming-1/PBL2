#include "Product.h"

// Constructor
Product::Product(int id, const string &name, const string &desc)
    : product_id(id), name(name), description(desc) {}

// Getters
int Product::getId() const { return product_id; }
string Product::getName() const { return name; }
string Product::getDescription() const { return description; }
// double Product::getPrice() const { return price; }

// Setters
void Product::setId(int id) { product_id = id; }
void Product::setName(const string &name) { this->name = name; }
void Product::setDescription(const string &desc) { description = desc; }
// void Product::setPrice(double price) { this->price = price; }

// Operator Overloads
bool Product::operator==(const Product &other) const { return product_id == other.product_id; }

istream &operator>>(istream &is, Product &product) {
    string productIdStr;
    getline(is, productIdStr, ',');
    getline(is, product.name, ',');
    // getline(is, product.description, ',');
    getline(is, product.description);
    // is >> product.price;
    product.product_id = stoi(productIdStr);
    return is;
}

ostream &operator<<(ostream &os, const Product &product) {
    // os << product.name << "," << product.description << "," << product.price;
    os << product.name << "," << product.description;
    return os;
}
