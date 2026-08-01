#ifndef ICOMBATANT_H
#define ICOMBATANT_H
#include <iostream>
namespace GameArena {
    class iCombatant{

        public:
        /* Damage this combatant would deal, before the target's defence. */
        virtual int attack() = 0;
        /* Resolves a strike against a target and returns the health actually
           removed. Separate from attack() because damage dealt and damage
           taken are different numbers once defence exists. */
        virtual int strike(iCombatant& target) = 0;
        virtual int defence() const = 0;
        virtual void takeDamage(int amount) = 0;
        virtual bool isAlive() = 0;
        virtual void display(std::ostream& os = std::cout) const= 0;
        virtual ~iCombatant() = default;
    };

}

#endif