#ifndef OrderItem_h
#define OrderItem_h

#include <iostream>
using namespace std;

class OrderItem
{
private:
    int product_id;
    int quantity;

public:
    OrderItem(int id = 0, int qty = 0);

    // Getters
    int getId() const;
    int getQuantity() const;

    // Setters
    void setId(int id);
    void setQuantity(int qty);

    // Operator Overloads
    bool operator==(const OrderItem &other) const;
    friend istream &operator>>(istream &is, OrderItem &item);
    friend ostream &operator<<(ostream &os, const OrderItem &item);
};

#endif
