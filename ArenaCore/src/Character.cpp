#include "Character.h"
#include <iostream>
#include <cstring>
#include <random>
using namespace std;

    namespace GameArena {
        
        namespace {
            /* One generator for the whole fight. Seeding it makes a run
               reproducible, which is what lets a test assert on exact damage
               and lets the browser replay the same fight as the binary. */
            std::mt19937& combatRng() {
                static std::mt19937 rng{std::random_device{}()};
                return rng;
            }
        }

        void Character::seedCombat(unsigned int seed){
            combatRng().seed(seed);
        }

        /* Damage lands within +/-20% of the base, so a stronger character is
           still favoured but the outcome is not fixed in advance. Always at
           least 1: a hit that removes nothing reads as a bug to a player. */
        int Character::rollDamage(int base){
            if (base <= 0) return 1;
            const int spread = base / 5;
            std::uniform_int_distribution<int> dist(base - spread, base + spread);
            const int rolled = dist(combatRng());
            return rolled < 1 ? 1 : rolled;
        }

        Character::Character(){
            m_name[0] = '\0';
            m_health = 0;
            m_maxHealth = 0;
            m_level = 0;
        }

        Character::Character(int level){
            m_name[0] = '\0';
            m_health = 0;
            m_maxHealth = 0;
            m_level = level;
        }

        Character::Character(const char* name, int health, int level){
            // strncpy with an explicit terminator: the source is a roster line
            // from a file, so its length is not ours to trust, and m_name is a
            // fixed 50 bytes.
            strncpy(m_name, name, sizeof(m_name) - 1);
            m_name[sizeof(m_name) - 1] = '\0';
            m_health = health;
            m_maxHealth = health;
            m_level = level;
        }


        Character::operator bool() const{
            return m_health > 0;
        }

        Character& Character::operator++(){
            ++m_level;
            return *this;
        }

        Character& Character::operator+=(int health){
            m_health += health;
            // Clamped at both ends: negative health made a corpse look more
            // dead the harder it was hit, and healing had no ceiling.
            if (m_health < 0) m_health = 0;
            if (m_maxHealth > 0 && m_health > m_maxHealth) m_health = m_maxHealth;
            return *this;
        }

        void Character::display(std::ostream& os) const{
            os << "Name: " << m_name << " | Health: " << m_health << " | Level: " << m_level << endl;
        }

        bool Character::isAlive() const{
            return m_health > 0;
        }

        const char* Character::getName() const{
            return m_name;
        }

        int Character::getHealth() const{
            return m_health;
        }

        int Character::getLevel() const{
            return m_level;
        }

        void Character::saveBase(std::ostream& os) const{
            os << m_name << "," << m_health << "," << m_level;
        }

        int Character::getMaxHealth() const{
            return m_maxHealth;
        }

        /* Defence is derived from level rather than stored, so levelling up
           makes a combatant harder to hurt as well as harder-hitting, and the
           roster file format is unchanged. */
        int Character::defence() const{
            return m_level / 2;
        }

        void Character::takeDamage(int amount){
            if (amount <= 0) return;
            *this += -amount;
        }

        /* Resolves one strike. Damage is rolled around this character's own
           output, then reduced by the target's defence — never below 1, so
           armour can blunt a hit but never make a combatant untouchable. */
        int Character::strike(iCombatant& target){
            if (!isAlive()) return 0;

            const int rolled = rollDamage(calculateDamage());
            const int mitigated = rolled - target.defence();
            const int dealt = mitigated < 1 ? 1 : mitigated;

            target.takeDamage(dealt);
            return dealt;
        }

        Character::~Character(){}

        bool operator==(const Character& c, const Character& ch){
            // Name is part of identity. Comparing only the stats made every
            // pair of equally-statted characters compare equal.
            return c.m_level == ch.m_level
                && c.m_health == ch.m_health
                && std::strcmp(c.m_name, ch.m_name) == 0;
        }
    }