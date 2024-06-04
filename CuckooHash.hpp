#pragma once

#include <vector>
#include <utility>
#include <string>
#include <iostream>

class CuckooHash {
private:
    std::vector<std::pair<int, std::string>> table1;
    std::vector<std::pair<int, std::string>> table2;
    size_t size;
    size_t numElements;
    const double maxLoadFactor = 0.9;

    size_t hash_function1(int key) const;
    size_t hash_function2(int key) const;
    bool insert_helper(int key, const std::string& value, std::vector<std::pair<int, std::string>>& table);
    void rehash();

public:
    CuckooHash(size_t size);

    void insert(int key, const std::string& value);
    void remove(int key);
    void print() const;
    size_t getSuccessfulInserts() const { return numElements; }
};

//Funkcje haszujące
size_t CuckooHash::hash_function1(int key) const {
    return key * 11 % size;
}

size_t CuckooHash::hash_function2(int key) const {
    return (key * (key + 11)) %  size;
}

//Pomocnicza funkcja do wstawiania elementów do tablicy mieszającej.
bool CuckooHash::insert_helper(int key, const std::string& value, std::vector<std::pair<int, std::string>>& table) {
    size_t index1 = hash_function1(key);

    if (table[index1].first == key) {//Sprawdzenie obecności klucza
        std::cout << "Klucz juz istnieje w tablicy!" << std::endl;
        return false;
    }

    size_t index2 = hash_function2(key);
    if (table[index2].first == key) {//Sprawdzenie obecności klucza
        std::cout << "Klucz juz istnieje w tablicy!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        size_t index = (index1 + i) % size; // Liniowe przeszukiwanie tablicy
        if (table[index].first == 0) {
            table[index] = std::make_pair(key, value);
            return true;
        }
        //warunek zakończenia pętli
        if (i == size - 1) {
            std::cout << "Brak miejsca w tablicy!" << std::endl;
            return false;
        }
    }

    // Rehash tablicy i spróbuj ponownie wstawić element pierwotny
    rehash();
    return insert_helper(key, value, table);
}

//Ponowne hashowanie tablicy mieszającej
void CuckooHash::rehash() {
    std::vector<std::pair<int, std::string>> oldTable1 = table1;
    std::vector<std::pair<int, std::string>> oldTable2 = table2;

    size *= 2;
    table1.clear();// Wyczyszczenie tablic
    table2.clear();
    table1.resize(size);// Zmiana rozmiaru tablic
    table2.resize(size);
    numElements = 0;//Ustawia liczbę elementów w tablicach na 0

    // Wstawienie elementów z poprzednich tablic do nowych
    for (const auto& pair : oldTable1) {
        if (pair.first != 0) {
            insert(pair.first, pair.second);
        }
    }
    for (const auto& pair : oldTable2) {
        if (pair.first != 0) {
            insert(pair.first, pair.second);
        }
    }
}

// Konstruktor
CuckooHash::CuckooHash(size_t size) : size(size), numElements(0) {
    table1.resize(size);
    table2.resize(size);
}

//Wstawianie pary klucz-wartosc
void CuckooHash::insert(int key, const std::string& value) {
    if (numElements >= size * maxLoadFactor) {// jesli ilosc elementow przekroczy 90% rozmiaru robimy rehash
        rehash();
    }

    // Wstawienie elementu do pierwszej lub drugiej tablicy
    if (insert_helper(key, value, table1) || insert_helper(key, value, table2)) {
        numElements++;
    }
    else {
        std::cout << "Tablice sa przepelnione!" << std::endl;
    }
}

//Usuwanie pary na podstawie klucza
void CuckooHash::remove(int key) {
    size_t index1 = hash_function1(key);
    size_t index2 = hash_function2(key);

    // Sprawdzenie, czy klucz znajduje się w pierwszej tablicy i jego ewentualne usunięcie
    if (table1[index1].first == key) {
        table1[index1] = std::make_pair(0, "");// Usunięcie elementu poprzez przypisanie pary zerowej
        numElements--;
        std::cout << "Klucz usuniety" << std::endl;
        return;
    }
    // Sprawdzenie, czy klucz znajduje się w drugiej tablicy i jego ewentualne usunięcie
    if (table2[index2].first == key) {
        table2[index2] = std::make_pair(0, "");// Usunięcie elementu poprzez przypisanie pary zerowej
        numElements--;
        std::cout << "Klucz usuniety" << std::endl;
        return;
    }
    std::cout << "Klucz nie istnieje w tablicy!" << std::endl;
}

//Wywietlanie i zliczanie elementów  w tablicy
void CuckooHash::print() const {
    std::cout << "Table 1:" << std::endl;
    int licznik = 0;
    for (size_t i = 0; i < size; ++i) {
        if (table1[i].first != 0) {
            std::cout << "{" << table1[i].first << ", " << table1[i].second << "}" << std::endl;
            licznik++;
        }
    }

    std::cout << "Table 2:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        if (table2[i].first != 0) {
            std::cout << "{" << table2[i].first << ", " << table2[i].second << "}" << std::endl;
            licznik++;
        }
    }
    std::cout << "Licznik: " << licznik << std::endl;
}
