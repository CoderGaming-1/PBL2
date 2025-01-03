#ifndef Order_h
#define Order_h

#include <iostream>
#include <string>
#include <ctime>
#include "Array.h"
#include "OrderItem.h"
#include "HashTable.h"
// #include "Product.h"
#include "Burger.h"
#include "Drink.h"
using namespace std;

class Order
{
public:
    int order_id;
    string customer_name;
    Array<OrderItem, 10> items;
    double total_amount;
    time_t datetime;

    Order(int id = 0, const string &name = "", const Array<OrderItem, 10> &items = {}, double total = 0.0,
          time_t dt = std::time(nullptr));

    // Getters
    int getId() const;
    string getCustomerName() const;
    Array<OrderItem, 10> getItems() const;
    double getTotalAmount() const;
    time_t getDatetime() const;

    // Setters
    void setId(int id);
    void setCustomerName(const string &name);
    void setItems(const Array<OrderItem, 10> &newItems);
    void setTotalAmount(double total);
    void setDatetime(time_t dt);

    // double calculateTotalAmount(const HashTable<Product>& productTable);
    double calculateTotalAmount(const HashTable<Burger>& burgerTable, const HashTable<Drink>& drinkTable);

    // Operator Overloads
    bool operator==(const Order &other) const;
    friend istream &operator>>(istream &is, Order &order);
    friend ostream &operator<<(ostream &os, const Order &order);
};

#endif
