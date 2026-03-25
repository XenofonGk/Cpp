#ifndef WARRIOR_H
#define WARRIOR_H
#include "Character.h"

    namespace GameArena {
        class Warrior : public Character{
            int* m_skillLevels{};
            int m_skillCount{};
        public:
            Warrior();
            Warrior(const char* name,int health, int level, int* skills, int count);
            Warrior(const Warrior& src);
            Warrior& operator=(const Warrior& src);
            ~Warrior();
            Warrior operator++(int);
            Warrior& operator+=(int skill);
            int attack() override;
            bool isAlive() override;
            int calculateDamage() override;
            void display(std::ostream& os = std::cout) const override;
        };
    }

#endif