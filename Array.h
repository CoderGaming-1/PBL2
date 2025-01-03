#ifndef Array_h
#define Array_h

#include <iostream>
using namespace std;

template <typename T, int MAX_SIZE>
class Array
{
public:
    T items[MAX_SIZE];
    int size;

    Array();

    bool add(const T &item);
    const T *get(int index) const;
    int getSize() const;

    T& operator[](int index);
    const T& operator[](int index) const;
    bool operator==(const Array<T, MAX_SIZE> &other) const;

    void readFile(const string &filename);
    void writeFile(const string &filename) const;

    template <typename U, int MS>
    friend ostream &operator<<(ostream &os, const Array<U, MS> &arr);
};
// #include "Array.cpp"
#endif
