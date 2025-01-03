#include "Array.h"
#include <fstream>
#include <sstream>

// Constructor
template <typename T, int MAX_SIZE>
Array<T, MAX_SIZE>::Array() : size(0) {}

// Add an item to the array
template <typename T, int MAX_SIZE>
bool Array<T, MAX_SIZE>::add(const T &item)
{
    if (size < MAX_SIZE)
    {
        items[size++] = item;
        return true;
    }
    return false;
}

// Get an item by index
template <typename T, int MAX_SIZE>
const T *Array<T, MAX_SIZE>::get(int index) const
{
    if (index >= 0 && index < size)
    {
        return &items[index];
    }
    return nullptr;
}

// Get the size of the array
template <typename T, int MAX_SIZE>
int Array<T, MAX_SIZE>::getSize() const
{
    return size;
}

template <typename T, int MAX_SIZE>
T& Array<T, MAX_SIZE>::operator[](int index)
{
    if (index >= 0 && index < size)
    {
        return items[index];
    }
    throw out_of_range("Index out of range");
}

template <typename T, int MAX_SIZE>
const T& Array<T, MAX_SIZE>::operator[](int index) const
{
    if (index >= 0 && index < size)
    {
        return items[index];
    }
    throw out_of_range("Index out of range");
}

template <typename T, int MAX_SIZE>
bool Array<T, MAX_SIZE>::operator==(const Array<T, MAX_SIZE> &other) const
{
    if (size != other.size)
    {
        return false;
    }
    for (int i = 0; i < size; ++i)
    {
        if (!(items[i] == other.items[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T, int MAX_SIZE>
void Array<T, MAX_SIZE>::readFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        T item;
        if (ss >> item) {
            add(item);
        }
    }

    file.close();
}

template <typename T, int MAX_SIZE>
void Array<T, MAX_SIZE>::writeFile(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << items[i] << endl;
    }

    file.close();
}

// Overload operator<< for printing
template <typename T, int MAX_SIZE>
ostream &operator<<(ostream &os, const Array<T, MAX_SIZE> &arr)
{
    for (int i = 0; i < arr.size; i++)
    {
        os << arr.items[i] << '\n';
    }
    return os;
}
