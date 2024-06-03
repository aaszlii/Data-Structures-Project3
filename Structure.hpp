#pragma once
#include <string>

class Structure {
public:
    virtual void insert(int key, const std::string& value) = 0;
    virtual bool remove(int key) = 0;
    virtual void print() const = 0;
};
