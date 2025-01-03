#include "Order.h"
#include <sstream>
#include <iomanip>
#include "OrderItem.h"
#include "Array.cpp"
#include "HashTable.cpp"
// #include "HashTable.h"
Order::Order(int id, const string &name, const Array<OrderItem, 10> &items, double total, time_t dt)
    : order_id(id), customer_name(name), items(items), total_amount(total), datetime(dt) {}
// Getters
int Order::getId() const {
    return order_id;
}
string Order::getCustomerName() const {
    return customer_name;
}
Array<OrderItem, 10> Order::getItems() const {
    return items;
}
double Order::getTotalAmount() const {
    return total_amount;
}
time_t Order::getDatetime() const {
    return datetime;
}

// Setters
void Order::setId(int id) {
    order_id = id;
}
void Order::setCustomerName(const string &name) {
    customer_name = name;
}
void Order::setItems(const Array<OrderItem, 10> &newItems) {
    items = newItems;
}
void Order::setTotalAmount(double total) {
    total_amount = total;
}
void Order::setDatetime(time_t dt) {
    datetime = dt;
}

// In Order.cpp, implement the function
double Order::calculateTotalAmount(const HashTable<Burger>& burgerTable, const HashTable<Drink>& drinkTable) {
    double total = 0.0;
    for (int i = 0; i < items.getSize(); ++i) {
        int productId = items[i].getId();
        int quantity = items[i].getQuantity();

        // Check if the product exists in the Burger table
        const Burger* burger = burgerTable[productId];
        if (burger) {
            total += burger->getPrice() * quantity;
            continue;
        }

        // Check if the product exists in the Drink table
        const Drink* drink = drinkTable[productId];
        if (drink) {
            total += drink->getPrice() * quantity;
            continue;
        }
    }

    this->total_amount = total;
    return total;
}

// Operator Overloads
bool Order::operator==(const Order &other) const {
    return order_id == other.order_id &&
           customer_name == other.customer_name &&
           total_amount == other.total_amount &&
           items == other.items; // Assuming Array class has an equality operator
}

istream &operator>>(istream &is, Order &order) {
    string line;
    if (getline(is, line)) {
        istringstream lineStream(line);
        string itemsStr, datetimeStr;
        char delimiter;

        lineStream >> order.order_id >> delimiter;
        getline(lineStream, order.customer_name, ',');
        if (lineStream.peek() == '"') {
            lineStream.get();
            getline(lineStream, itemsStr, '"');
            lineStream.ignore(1, ',');
        }
        lineStream >> order.total_amount >> delimiter;
        getline(lineStream, datetimeStr);

        // Parse datetime
        tm tm = {};
        istringstream datetimeStream(datetimeStr);
        datetimeStream >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
        order.datetime = mktime(&tm);

        istringstream itemsStream(itemsStr);
        Array<OrderItem, 10> itemsArray;
        string itemStr;
        while (getline(itemsStream, itemStr, ';')) {
            istringstream itemStream(itemStr);
            int productId, quantity;
            if (itemStream >> productId >> delimiter >> quantity) {
                OrderItem newItem(productId, quantity);
                itemsArray.add(newItem);
            }
        }
        order.setItems(itemsArray);
    }
    return is;
}


ostream &operator<<(ostream &os, const Order &order) {
    os << order.order_id << ','
       << order.customer_name << ",\"";
    auto itemsArray = order.getItems();
    for (int i = 0; i < itemsArray.getSize(); ++i) {
        OrderItem item = itemsArray[i];
        if (i > 0) os << ';';
        os << item.getId() << ',' << item.getQuantity();
    }
    os << "\"," << order.total_amount << ',';

    // Format datetime
    os << put_time(localtime(&order.datetime), "%Y-%m-%d %H:%M:%S");
    return os;
}

