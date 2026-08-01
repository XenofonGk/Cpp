#include "Character.h"
#include <iostream>
#include <cstring>
using namespace std;

    namespace GameArena {
        
        Character::Character(){
            m_name[0] = '\0';
            m_health = 0;
            m_level = 0;
        }

        Character::Character(int level){
            m_name[0] = '\0';
            m_health = 0;
            m_level = level;
        }

        Character::Character(const char* name, int health, int level){
            // strncpy with an explicit terminator: the source is a roster line
            // from a file, so its length is not ours to trust, and m_name is a
            // fixed 50 bytes.
            strncpy(m_name, name, sizeof(m_name) - 1);
            m_name[sizeof(m_name) - 1] = '\0';
            m_health = health;
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

        Character::~Character(){}

        bool operator==(const Character& c, const Character& ch){
            // Name is part of identity. Comparing only the stats made every
            // pair of equally-statted characters compare equal.
            return c.m_level == ch.m_level
                && c.m_health == ch.m_health
                && std::strcmp(c.m_name, ch.m_name) == 0;
        }
    }