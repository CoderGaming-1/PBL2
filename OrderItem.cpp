#include "OrderItem.h"

// Constructor
OrderItem::OrderItem(int id, int qty) : product_id(id), quantity(qty) {}

// Getters
int OrderItem::getId() const { return product_id; }
int OrderItem::getQuantity() const { return quantity; }

// Setters
void OrderItem::setId(int id) { product_id = id; }
void OrderItem::setQuantity(int qty) { quantity = qty; }

// Operator Overloads
bool OrderItem::operator==(const OrderItem &other) const { return product_id == other.product_id; }

istream &operator>>(istream &is, OrderItem &item) {
    char delimiter;
    is >> item.product_id >> delimiter >> item.quantity;
    return is;
}

ostream &operator<<(ostream &os, const OrderItem &item) {
    os << item.product_id << "," << item.quantity;
    return os;
}
