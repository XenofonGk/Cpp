#ifndef CHARACTER_H
#define CHARACTER_H
#include "iCombatant.h"

    namespace GameArena {
        class Character : public iCombatant {
            private:
                char m_name[50]{};
                int m_health{};
                int m_maxHealth{};
                int m_level{};
            protected:
                // Writes the "name,health,level" portion shared by every
                // subclass, so derived save() implementations only add their
                // own fields.
                void saveBase(std::ostream& os) const;
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
                // Accessors. Without these the only way to read a character's
                // state is to print it, which forces anything driving the model
                // — tests, another UI, a WebAssembly build — to parse text.
                const char* getName() const;
                int getHealth() const;
                int getLevel() const;
                int getMaxHealth() const;
                int defence() const override;

                /* Damage varies within a band around calculateDamage() so a
                   fight is not decided before it starts. The generator is
                   shared and seedable — seedCombat() makes a run reproducible,
                   which is what lets tests assert on exact numbers and lets the
                   same seed replay identically in the browser. */
                static void seedCombat(unsigned int seed);
                static int rollDamage(int base);

                int strike(iCombatant& target) override;
                void takeDamage(int amount) override;

                virtual int calculateDamage() = 0;
                // Each subclass writes the line format Arena::load() can read
                // back, which is what makes save/load round trip.
                virtual void save(std::ostream& os) const = 0;
                virtual ~Character();
                friend bool operator==(const Character&, const Character&);
            };
        
    }

#endif