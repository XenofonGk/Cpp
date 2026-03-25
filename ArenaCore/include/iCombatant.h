#ifndef ICOMBATANT_H
#define ICOMBATANT_H
#include <iostream>
namespace GameArena {
    class iCombatant{

        public:
        virtual int attack() = 0;
        virtual bool isAlive() = 0;
        virtual void display(std::ostream& os = std::cout) const= 0;
        virtual ~iCombatant() = default;
    };

}

#endif