#include "Input.h"
#include <iostream>

    namespace GameArena {
        int readInt(int min,int max){
            int value;
            bool valid = true;
            do {
                std::cout << "Enter Your Next Action";
                std::cin >> value;

                if (std::cin.fail()){
                    std::cerr << "Invalid Menu Item! Try Again..." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(2000, '\n');
                } else if (value < min || value > max){
                    std::cerr << value << " is outside the range [" << min << ", " << max << "]" << std::endl;
                    std::cerr << "Invalid Input! Try Again..." << std::endl;
                    std::cin.ignore(2000, '\n');
                } else if (char(std::cin.get()) != '\n'){
                    std::cerr << "Trailing characters! Try Again..." << std::endl;
                    std::cin.ignore(2000, '\n');
                }  else valid = false;
            } while (valid);
            return value;
        }

    }