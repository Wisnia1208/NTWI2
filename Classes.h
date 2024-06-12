#pragma once

#include <string>
#include "Functions.h"

class Car {
protected:
    std::string model = "";
    int capacity = 500;
public:
    void setModel(std::string name) {
        model = name;
    }
    std::string getModel() {
        return model;
    }

    void setCapacity(int x) {
        try {
            if (x >= 0) {
                capacity = x;
            }
            else {
                throw(x);
            }
        }
        catch (int e) {
            std::cout << "error setCapacity() - input: " << e << " is below 0\n";
        }
    }
    int getCapacity() {
        return capacity;
    }

    Car(std::string name, int cap) {
        model = name;
        if (cap >= 0) {
            capacity = cap;
        }
        else {
            std::cout << "incorrect input CAPACITY\n";
        }
    }

    Car(std::string name) {
        model = name;
    }

    ~Car() {}
};