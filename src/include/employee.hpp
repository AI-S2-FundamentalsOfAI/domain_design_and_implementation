#pragma once
#include <iostream>
#include <ostream>

class Employee {
private:
    std::string     name;
    bool            busy;
    bool            forklift_certificate;
public:
    friend std::ostream & operator<<(std::ostream &os, const Employee &obj) {
        return os
               << "name: " << obj.name
               << " busy: " << obj.busy
               << " forklift_certificate: " << obj.forklift_certificate;
    }
};
