#pragma once

#include <vector>
#include <utility>
#include <iostream> // Dodano do obsługi strumienia wejścia-wyjścia

class CuckooHash {
private:
    std::vector<std::pair<int, std::string>> table1;
    std::vector<std::pair<int, std::string>> table2;
    size_t size;
    size_t hash_function1(int key) const;
    size_t hash_function2(int key) const;
    bool insert_helper(int key, const std::string& value, std::vector<std::pair<int, std::string>>& table);

public:
    CuckooHash(size_t size);

    void insert(int key, const std::string& value);
    void remove(int key);
    void print() const; // Dodano deklarację metody print()
};
size_t CuckooHash::hash_function1(int key) const {
    return key % size;
}

size_t CuckooHash::hash_function2(int key) const {
    return (key / size) % size;
}

bool CuckooHash::insert_helper(int key, const std::string& value, std::vector<std::pair<int, std::string>>& table) {
    size_t index1 = hash_function1(key);
    size_t index2 = hash_function2(key);

    if (table[index1].first == key || table[index2].first == key) {
        std::cerr << "Klucz juz istnieje w tablicy!" << std::endl;
        return false;
    }

    if (table[index1].first == 0) {
        table[index1] = std::make_pair(key, value);
        return true;
    }

    if (table[index2].first == 0) {
        table[index2] = std::make_pair(key, value);
        return true;
    }

    for (int i = 0; i < size; ++i) {
        std::swap(table[index1], table[index2]);
        if (table[index1].first == 0) {
            table[index1] = std::make_pair(key, value);
            return true;
        }
        index1 = hash_function1(table[index1].first);
        index2 = hash_function2(table[index2].first);
    }

    std::cerr << "Brak miejsca w tablicy!" << std::endl;
    return false;
}

CuckooHash::CuckooHash(size_t size) : size(size) {
    table1.resize(size);
    table2.resize(size);
}

void CuckooHash::insert(int key, const std::string& value) {
    if (!insert_helper(key, value, table1) && !insert_helper(key, value, table2)) {
        std::cerr << "Tablice sa przepełnione!" << std::endl;
    }
}

void CuckooHash::remove(int key) {
    size_t index1 = hash_function1(key);
    size_t index2 = hash_function2(key);

    if (table1[index1].first == key) {
        table1[index1] = std::make_pair(0, "");
        std::cout << "Klucz usuniety" << std::endl;
        return;
    }
    if (table2[index2].first == key) {
        table2[index2] = std::make_pair(0, "");
        std::cout << "Klucz usuniety" << std::endl;
        return;
    }

    std::cerr << "Klucz nie istnieje w tablicy!" << std::endl; // Dodano komunikat
}
void CuckooHash::print() const {
    std::cout << "Table 1:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        if (table1[i].first != 0) {
            std::cout << "[" << i << "]: {" << table1[i].first << ", " << table1[i].second << "}" << std::endl;
        }
        
    }

    std::cout << "Table 2:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        if (table2[i].first != 0) {
            std::cout << "[" << i << "]: {" << table2[i].first << ", " << table2[i].second << "}" << std::endl;
        }
        
    }
}

