#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    int capacity;
    int size;

    void resize(int new_capacity) {
        int* new_data = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {
        resize(1); // Start with capacity 1
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size == 0) throw std::underflow_error("Array is empty");
        size--;
        if (size <= capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) resize(capacity * 2);
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void erase(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
        if (size <= capacity / 4 && capacity > 1) resize(capacity / 2);
    }

    int get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void set(int index, int value) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    int get_size() const {
        return size;
    }

    int get_capacity() const {
        return capacity;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    int* begin() { return data; }
    int* end() { return data + size; }
};

// Example usage
int main() {
    DynamicArray arr;
    for (int i = 1; i <= 10; ++i) arr.push_back(i);
    arr.print();

    arr.pop_back();
    arr.pop_back();
    arr.print();

    arr.set(0, 99);
    std::cout << "First element: " << arr.get(0) << std::endl;
    std::cout << "Size: " << arr.get_size() << ", Capacity: " << arr.get_capacity() << std::endl;

    arr.insert(5, 42);
    arr.print();

    arr.erase(5);
    arr.print();

    std::cout << "Iterating: ";
    for (int* it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
