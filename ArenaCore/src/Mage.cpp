#include "Mage.h"
#include "Character.h"
#include <iostream>

    namespace GameArena {
        Mage::Mage() {
            m_SpellPower = nullptr;
            m_SpellCount = 0;
        }
        Mage::Mage(const char* name,int health, int level, int* skills, int count)
        : Character(name, health, level){
            m_SpellCount = count;
            m_SpellPower = new int[m_SpellCount];
            for (int i = 0; i < m_SpellCount; i++){
                m_SpellPower[i] = skills[i];
            } 
        }

        Mage::Mage(const Mage& src){
            m_SpellPower = nullptr;
            *this = src;
        }

        Mage& Mage::operator=(const Mage& src){
            if (this != &src) {
                delete[] m_SpellPower;
                 m_SpellCount = src.m_SpellCount;
                 if (src.m_SpellPower != nullptr){
            m_SpellPower = new int[src.m_SpellCount];
            for (int i = 0; i < m_SpellCount; i++){
                m_SpellPower[i] = src.m_SpellPower[i];
            }  } else {
                m_SpellPower = nullptr;
            }
        }
        return *this;
        }
        
        Mage::~Mage(){
            delete[] m_SpellPower;
            m_SpellPower = nullptr;
        }
        Mage Mage::operator++(int){
            Mage copy = *this;
            Character::operator++();
            return copy;
        }
        Mage& Mage::operator+=(int skill){
            int* temp{};
            temp = new int[m_SpellCount + 1];
            for (int i = 0; i < m_SpellCount; i++){
                temp[i] = m_SpellPower[i];
            }
             temp[m_SpellCount] = skill;
             delete[] m_SpellPower;
             m_SpellPower = temp;
             m_SpellPower++;

             return *this;
        }
        
        int Mage::attack(){
           return calculateDamage();
        }

        bool Mage::isAlive(){
            return Character::isAlive();
        }
        int Mage::calculateDamage(){
            int dmg = 1;
                for ( int i = 0; i < m_SpellCount; i++){
                    dmg += m_SpellPower[i];
                }
                return dmg;
        }
        void Mage::display(std::ostream& os) const{
            Character::display(os);

            for (int j = 0; j < m_SpellCount; j++){

            os << "Spell" << j + 1  << ": " << m_SpellPower[j] << "\n";
            
        }
    }
}