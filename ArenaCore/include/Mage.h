#ifndef WARRIOR_H
#define WARRIOR_H
#include "Character.h"

    namespace GameArena {
        class Mage : public Character{
            int* m_SpellPower{};
            int m_SpellCount{};
        public:
            Mage();
            Mage(const char* name,int health, int level, int* skills, int count);
            Mage(const Mage& src);
            Mage& operator=(const Mage& src);
            ~Mage();
            Mage operator++(int);
            Mage& operator+=(int skill);
            int attack() override;
            bool isAlive() override;
            int calculateDamage() override;
            void display(std::ostream& os = std::cout) const override;
        };
    }

#endif