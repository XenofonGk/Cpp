#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
namespace Ikariam {


class Building {
    char* m_name{};
    int m_level{1};

    public:
    Building(const char* name, int level = 1); // 3 argument constructor
    // Rule Of Three
    Building(const Building& src); // Deep copy the name
    Building& operator=(const Building& src); // Clean up old memory, check for self-assignment,then deep copy
    virtual ~Building(); // Clean up the heap

    // Polymorphism
    virtual void print(std::ostream& os) const = 0;
    virtual Building* clone() const = 0;

    // Helper to get the name
    const char* getName() const;
};
    // Global helper
    std::ostream& operator<<(std::ostream& os, const Building& b);

   
}
#endif 