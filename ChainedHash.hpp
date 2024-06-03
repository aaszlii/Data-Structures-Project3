#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>

class ChainedHash {
private:
    size_t size;
    std::vector<std::list<std::pair<int, std::string>>> table;
    size_t hash(int key) const;

public:
    ChainedHash(size_t size);
    void insert(int key, const std::string& value);
    void remove(int key);
    void print() const;
};

size_t ChainedHash::hash(int key) const {
    return std::hash<int>{}(key) % size;
}

ChainedHash::ChainedHash(size_t size) : size(size), table(size) {}

void ChainedHash::insert(int key, const std::string& value) {
    size_t pos = hash(key);
    for (auto& pair : table[pos]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    table[pos].emplace_back(key, value);
}

void ChainedHash::remove(int key) {
    size_t pos = hash(key);
    auto& chain = table[pos];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            chain.erase(it);
            return;
        }
    }
    throw std::runtime_error("Key not found");
}

void ChainedHash::print() const {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Kubelek " << i << ": ";
        for (const auto& pair : table[i]) {
            std::cout << "{" << pair.first << ", " << pair.second << "} ";
        }
        
    }
}
