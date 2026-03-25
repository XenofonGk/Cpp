#ifndef GAMEARENA_H
#define GAMEARENA_H
#include "Mage.h"
#include "Warrior.h"

    namespace GameArena{

        class Arena{
        Character** m_roster{};
        int m_count{};
    public:
        Arena();
        Arena(const Arena& src) = delete;
        Arena& operator=(const Arena& src) = delete;
        ~Arena();
        Character* getCharacter(int index) const;
        Arena& operator+=(Arena*);
        void load(const char* filename);
        void save(const char* filename) const;
        void display(std::ostream& os = std::cout) const;
        
        };
        std::ostream& operator<<(std::ostream& os, const Character& c);

    }

#endif