#ifndef CHARACTER_H
#define CHARACTER_H
#include "iCombatant.h"

    namespace GameArena {
        class Character : public iCombatant {
            private:
                char m_name[50]{};
                int m_health{};
                int m_level{};
            public:
                Character();
                Character(int level);
                Character(const char* name, int health, int level);
                operator bool() const;
                Character& operator++();
                Character operator++(int);
                Character& operator+=(int);
                void display(std::ostream& os) const;
                bool isAlive() const;
                virtual int calculateDamage() = 0;
                virtual ~Character();
                friend bool operator==(const Character&, const Character&);
            };
        
    }

#endif