#include "HashTable.h"
#include <Product.h>
#include <Burger.h>
#include <Drink.h>
#include <HashTable.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Constructor
template <typename T>
HashTable<T>::HashTable() : tableSize(INITIAL_SIZE), elementCount(0)
{
    table = new T[tableSize];
    occupied = new bool[tableSize]{false};
    tombstone = new bool[tableSize]{false};
}

// Destructor
template <typename T>
HashTable<T>::~HashTable()
{
    delete[] table;
    delete[] occupied;
    delete[] tombstone;
}

// Hash Function
template <typename T>
int HashTable<T>::hash(int key) const
{
    return key % tableSize;
}

// Quadratic Probing
template <typename T>
int HashTable<T>::quadraticProbe(int key, int attempt) const
{
    return (hash(key) + attempt * attempt) % tableSize;
}

// Get Next Prime Size
template <typename T>
int HashTable<T>::getNextPrimeSize() const
{
    for (int i = 0; i < PRIME_COUNT; ++i)
    {
        if (PRIMES[i] > tableSize)
            return PRIMES[i];
    }
    return tableSize * 2; // Fallback to doubling size
}

// Resize the Hash Table
template <typename T>
void HashTable<T>::resize()
{
    int oldSize = tableSize;
    tableSize = getNextPrimeSize();
    T *oldTable = table;
    bool *oldOccupied = occupied;
    bool *oldTombstone = tombstone;

    table = new T[tableSize];
    occupied = new bool[tableSize]{false};
    tombstone = new bool[tableSize]{false};
    elementCount = 0;

    for (int i = 0; i < oldSize; ++i)
    {
        if (oldOccupied[i] && !oldTombstone[i])
        {
            add(oldTable[i]);
        }
    }

    delete[] oldTable;
    delete[] oldOccupied;
    delete[] oldTombstone;
}

// Add an item to the Hash Table
template <typename T>
bool HashTable<T>::add(const T &item)
{
    if (elementCount > tableSize * MAX_LOAD_FACTOR)
    {
        resize();
    }

    int key = item.getId();
    int firstTombstone = -1;

    for (int attempt = 0; attempt < tableSize; ++attempt)
    {
        int index = quadraticProbe(key, attempt);

        if (!occupied[index])
        {
            if (firstTombstone != -1)
                index = firstTombstone; // Use first tombstone if available

            table[index] = item;
            occupied[index] = true;
            tombstone[index] = false;
            ++elementCount;
            return true;
        }
        else if (tombstone[index] && firstTombstone == -1)
        {
            firstTombstone = index;
        }
        else if (table[index] == item)
        {
            return false; // Duplicate item
        }
    }
    return false; // Table is full
}

// Access an item by its ID
template <typename T>
const T *HashTable<T>::operator[](int id) const
{
    for (int attempt = 0; attempt < tableSize; ++attempt)
    {
        int index = quadraticProbe(id, attempt);
        if (occupied[index] && !tombstone[index] && table[index].getId() == id)
        {
            return &table[index];
        }
        else if (!occupied[index])
        {
            return nullptr;
        }
    }
    return nullptr;
}

// Update an item in the Hash Table
template <typename T>
bool HashTable<T>::update(int id, const T &newItem)
{
    for (int attempt = 0; attempt < tableSize; ++attempt)
    {
        int index = quadraticProbe(id, attempt);
        if (occupied[index] && !tombstone[index] && table[index].getId() == id)
        {
            table[index] = newItem;
            return true;
        }
        else if (!occupied[index])
        {
            return false;
        }
    }
    return false;
}

// Remove an item from the Hash Table
template <typename T>
bool HashTable<T>::remove(int id)
{
    for (int attempt = 0; attempt < tableSize; ++attempt)
    {
        int index = quadraticProbe(id, attempt);
        if (occupied[index] && !tombstone[index] && table[index].getId() == id)
        {
            tombstone[index] = true;
            --elementCount;
            return true;
        }
        else if (!occupied[index])
        {
            return false;
        }
    }
    return false;
}

template <typename T>
bool HashTable<T>::isExist(int id)
{
    for (int attempt = 0; attempt < tableSize; ++attempt)
    {
        int index = quadraticProbe(id, attempt);
        if (occupied[index] && !tombstone[index] && table[index].getId() == id)
        {
            return true;
        }
        else if (!occupied[index])
        {
            return false;
        }
    }
    return false;
}

// template <typename T>
// void HashTable<T>::sortByPrice(bool ascending) {
//     Array<T, 211> arr;
//     int index = 0;

//     for (int i = 0; i < tableSize; ++i) {
//         if (occupied[i] && !tombstone[i]) {
//             arr.add(table[i]);
//         }
//     }

//     auto compare = [ascending](const T &a, const T &b) {
//         if (ascending) {
//             return a.getPrice() < b.getPrice();
//         } else {
//             return a.getPrice() > b.getPrice();
//         }
//     };

//     sort(arr.items, arr.items + arr.getSize(), compare);

//     for (int i = 0; i < arr.getSize(); ++i) {
//         cout << arr[i] << endl;
//     }
// }

// template <typename T>
// void quickSort(Array<T, 211> &arr, int low, int high, bool ascending) {
//     if (low < high) {
//         int pivotIndex = partition(arr, low, high, ascending);
//         quickSort(arr, low, pivotIndex - 1, ascending);
//         quickSort(arr, pivotIndex + 1, high, ascending);
//     }
// }

// template <typename T>
// int partition(Array<T, 211> &arr, int low, int high, bool ascending) {
//     T pivot = arr[high];
//     int i = low - 1;
//     for (int j = low; j < high; ++j) {
//         if ((ascending && arr[j].getPrice() <= pivot.getPrice()) ||
//             (!ascending && arr[j].getPrice() >= pivot.getPrice())) {
//             ++i;
//             swap(arr[i], arr[j]);
//         }
//     }
//     swap(arr[i + 1], arr[high]);
//     return i + 1;
// }

// template <typename T>
// void HashTable<T>::sortByPrice(bool ascending) {
//     Array<T, 211> arr;
//     for (int i = 0; i < tableSize; ++i) {
//         if (occupied[i] && !tombstone[i]) {
//             arr.add(table[i]);
//         }
//     }
//     quickSort(arr, 0, arr.getSize() - 1, ascending);
//     for (int i = 0; i < arr.getSize(); ++i) {
//         cout << arr[i] << endl;
//     }
// }

// template <typename T>
// void HashTable<T>::sortByTotal(bool ascending) {
//     Array<T, 211> arr;
//     int index = 0;

//     for (int i = 0; i < tableSize; ++i) {
//         if (occupied[i] && !tombstone[i]) {
//             arr.add(table[i]);
//         }
//     }

//     auto compare = [ascending](const T &a, const T &b) {
//         if (ascending) {
//             return a.getTotalAmount() < b.getTotalAmount();
//         } else {
//             return a.getTotalAmount() > b.getTotalAmount();
//         }
//     };

//     sort(arr.items, arr.items + arr.getSize(), compare);

//     for (int i = 0; i < arr.getSize(); ++i) {
//         cout << arr[i] << endl;
//     }
// }

template <typename T>
void quickSortByPrice(Array<T, 211> &arr, int low, int high, bool ascending) {
    if (low < high) {
        int pivotIndex = partitionByPrice(arr, low, high, ascending);
        quickSortByPrice(arr, low, pivotIndex - 1, ascending);
        quickSortByPrice(arr, pivotIndex + 1, high, ascending);
    }
}

template <typename T>
int partitionByPrice(Array<T, 211> &arr, int low, int high, bool ascending) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if ((ascending && arr[j].getPrice() <= pivot.getPrice()) ||
            (!ascending && arr[j].getPrice() >= pivot.getPrice())) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void HashTable<T>::sortByPrice(bool ascending) {
    Array<T, 211> arr;
    for (int i = 0; i < tableSize; ++i) {
        if (occupied[i] && !tombstone[i]) {
            arr.add(table[i]);
        }
    }

    quickSortByPrice(arr, 0, arr.getSize() - 1, ascending);

    for (int i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << endl;
    }
}

template <typename T>
void quickSortByTotal(Array<T, 211> &arr, int low, int high, bool ascending) {
    if (low < high) {
        int pivotIndex = partitionByTotal(arr, low, high, ascending);
        quickSortByTotal(arr, low, pivotIndex - 1, ascending);
        quickSortByTotal(arr, pivotIndex + 1, high, ascending);
    }
}

template <typename T>
int partitionByTotal(Array<T, 211> &arr, int low, int high, bool ascending) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if ((ascending && arr[j].getTotalAmount() <= pivot.getTotalAmount()) ||
            (!ascending && arr[j].getTotalAmount() >= pivot.getTotalAmount())) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// template <typename T>
// void HashTable<T>::sortByTotal(bool ascending) {
//     Array<T, 211> arr;
//     for (int i = 0; i < tableSize; ++i) {
//         if (occupied[i] && !tombstone[i]) {
//             arr.add(table[i]);
//         }
//     }

//     quickSortByTotal(arr, 0, arr.getSize() - 1, ascending);

//     for (int i = 0; i < arr.getSize(); ++i) {
//         cout << arr[i] << endl;
//     }
// }

template <typename T>
void HashTable<T>::sortByTotal(bool ascending, time_t startTime, time_t endTime) {
    // Print the time range
    cout << "Sorting by total within the date range: "
         << put_time(localtime(&startTime), "%Y-%m-%d %H:%M:%S")
         << " to "
         << put_time(localtime(&endTime), "%Y-%m-%d %H:%M:%S")
         << '\n';

    Array<T, 211> arr;

    // Filter the elements based on the time range
    for (int i = 0; i < tableSize; ++i) {
        if (occupied[i] && !tombstone[i]) {
            if (table[i].datetime >= startTime && table[i].datetime <= endTime) {
                arr.add(table[i]);
            }
        }
    }

    // Perform sorting on the filtered array
    quickSortByTotal(arr, 0, arr.getSize() - 1, ascending);

    // Output the sorted list
    for (int i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << endl;
    }
}


template <typename T>
void HashTable<T>::readFile(const string &filename)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        T item;
        if (ss >> item)
        {
            add(item);
        }
    }

    inFile.close();
}

template <typename T>
void HashTable<T>::writeFile(const string &filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    for (int i = 0; i < tableSize; ++i)
    {
        if (occupied[i] && !tombstone[i])
        {
            file << table[i] << '\n';
        }
    }

    file.close();
}

// Print the Hash Table
template <typename T>
ostream &operator<<(ostream &os, const HashTable<T> &hashTable)
{
    for (int i = 0; i < hashTable.tableSize; ++i)
    {
        if (hashTable.occupied[i] && !hashTable.tombstone[i])
        {
            os << hashTable.table[i] << '\n';
        }
    }
    return os;
}

// Prime Numbers Array
template <typename T>
const int HashTable<T>::PRIMES[] = {101, 211, 431, 863, 1723, 3467, 6949, 14033, 28067};

// Load Factor
template <typename T>
const float HashTable<T>::MAX_LOAD_FACTOR = 0.7;
