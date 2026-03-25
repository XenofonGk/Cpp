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
            strcpy(m_name,name);
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

        Character::~Character(){}

        bool operator==(const Character& c, const Character& ch){
            return c.m_level == ch.m_level && c.m_health == ch.m_health;

        }
    }