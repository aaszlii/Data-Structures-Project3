#pragma once

#include <iostream> // Dodano do obsługi strumienia wejścia-wyjścia
#include <vector>
#include <string>
#include <stdexcept>

class OpenAddressingHash {
private:
    size_t size;
    std::vector<std::pair<int, std::string>> table;
    std::vector<bool> occupied;
    size_t hash(int key, size_t i) const;

public:
    OpenAddressingHash(size_t size);
    void insert(int key, const std::string& value);
    bool remove(int key);
    void print() const; // Dodano deklarację metody print()
};

size_t OpenAddressingHash::hash(int key, size_t i) const {
    return (std::hash<int>{}(key)+i) % size;
}

OpenAddressingHash::OpenAddressingHash(size_t size)
    : size(size), table(size), occupied(size, false) {}

void OpenAddressingHash::insert(int key, const std::string& value) {
    for (size_t i = 0; i < size; ++i) {
        size_t pos = hash(key, i);
        if (!occupied[pos]) {
            table[pos] = std::make_pair(key, value);
            occupied[pos] = true;
            return;
        }
    }
    throw std::runtime_error("Hash table is full");
}

bool OpenAddressingHash::remove(int key) {
    for (size_t i = 0; i < size; ++i) {
        size_t pos = hash(key, i);
        if (occupied[pos] && table[pos].first == key) {
            occupied[pos] = false;
            return true; // Klucz został usunięty poprawnie
        }
    }
    return false; // Klucz nie został znaleziony w tablicy
}

void OpenAddressingHash::print() const {
    for (size_t i = 0; i < size; ++i) {
        if (occupied[i]) {
            std::cout << "Key: " << table[i].first << ", Value: " << table[i].second << "\n";
        }
        
    }
}
