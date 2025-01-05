#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include "Array.h"
using namespace std;

template <typename T>
class HashTable
{
protected:
    static const int INITIAL_SIZE = 211;
    static const float MAX_LOAD_FACTOR;
    static inline const int PRIMES[] = {101, 211, 431, 863, 1723, 3467, 6949, 14033, 28067};
    static const int PRIME_COUNT = 9;

    T *table;
    bool *occupied;
    bool *tombstone;
    int tableSize;
    int elementCount;

    int hash(int key) const;
    int quadraticProbe(int key, int attempt) const;
    int getNextPrimeSize() const;
    void resize();

public:
    HashTable();
    ~HashTable();

    bool add(const T &item);
    const T *operator[](int id) const;
    bool update(int id, const T &newItem);
    bool remove(int id);
    bool isExist(int id);
    int getUsedSlot() const;

    Array<T, 211> sortByPrice(bool ascending);
    Array<T, 211> sortByTotal(bool ascending, time_t startTime, time_t endTime);

    void readFile(const string &filename);
    void writeFile(const string &filename) const;

    template <typename U>
    friend ostream &operator<<(ostream &os, const HashTable<U> &hashTable);

    int getTableSize() const {
        return tableSize;
    }

    bool isOccupied(int index) const {
        return occupied[index];
    }

    bool isTombstone(int index) const {
        return tombstone[index];
    }

    const T& getItemAt(int index) const {
        return table[index];
    }
};

// #include "HashTable.cpp"
#endif
