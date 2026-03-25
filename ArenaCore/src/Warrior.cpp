#include "Warrior.h"
#include "Character.h"
#include <iostream>

    namespace GameArena {
        Warrior::Warrior() {
            m_skillLevels = nullptr;
            m_skillCount = 0;
        }
        Warrior::Warrior(const char* name,int health, int level, int* skills, int count)
        : Character(name, health, level){
            m_skillCount = count;
            m_skillLevels = new int[m_skillCount];
            for (int i = 0; i < m_skillCount; i++){
                m_skillLevels[i] = skills[i];
            } 
        }

        Warrior::Warrior(const Warrior& src){
            m_skillLevels = nullptr;
            *this = src;
        }

        Warrior& Warrior::operator=(const Warrior& src){
            if (this != &src) {
                delete[] m_skillLevels;
                 m_skillCount = src.m_skillCount;
                 if (src.m_skillLevels != nullptr){
            m_skillLevels = new int[src.m_skillCount];
            for (int i = 0; i < m_skillCount; i++){
                m_skillLevels[i] = src.m_skillLevels[i];
            }  } else {
                m_skillLevels = nullptr;
            }
        }
        return *this;
        }
        
        Warrior::~Warrior(){
            delete[] m_skillLevels;
            m_skillLevels = nullptr;
        }
        Warrior Warrior::operator++(int){
            Warrior copy = *this;
            Character::operator++();
            return copy;
        }
        Warrior& Warrior::operator+=(int skill){
            int* temp{};
            temp = new int[m_skillCount + 1];
            for (int i = 0; i < m_skillCount; i++){
                temp[i] = m_skillLevels[i];
            }
             temp[m_skillCount] = skill;
             delete[] m_skillLevels;
             m_skillLevels = temp;
             m_skillCount++;

             return *this;
        }
        
        int Warrior::attack(){
           return calculateDamage();
        }

        bool Warrior::isAlive(){
            return Character::isAlive();
        }
        int Warrior::calculateDamage(){
            int dmg{};
                for ( int i = 0; i < m_skillCount; i++){
                    dmg += m_skillLevels[i];
                }
                return dmg;
        }
        void Warrior::display(std::ostream& os) const{
            Character::display(os);

            for (int i = 0; i < m_skillCount; i++){

            os << "Skill" << i + 1  << ": " << m_skillLevels[i] << "\n";
            
        }
    }