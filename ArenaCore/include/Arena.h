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
        // The roster is owned through raw pointers, so rather than deep-copying
        // an abstract base, copying is deleted outright and ownership stays
        // unambiguous.
        Arena(const Arena& src) = delete;
        Arena& operator=(const Arena& src) = delete;
        ~Arena();
        int size() const;
        Character* getCharacter(int index) const;
        // Appends a character and takes ownership of it.
        Arena& operator+=(Character* combatant);
        void load(const char* filename);
        void save(const char* filename) const;
        void display(std::ostream& os = std::cout) const;

        /* One exchange between two roster members: the faster acts first, the
           survivor strikes back if still standing. Returns the index of the
           winner, or -1 while both are alive.

           Turn order is by level, so a levelling decision changes who lands the
           first blow — the only place in this project where a player choice
           alters an outcome. */
        int fight(int indexA, int indexB, std::ostream& os = std::cout);
        
        };
        std::ostream& operator<<(std::ostream& os, const Character& c);

    }

#endif