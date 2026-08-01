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

        Warrior::Warrior(const Warrior& src) : Character(src){
            // Character(src) is essential: without it the base subobject is
            // default-constructed and the copy silently loses name, health and
            // level, because operator= below only handles the array.
            m_skillLevels = nullptr;
            m_skillCount = 0;
            *this = src;
        }

        Warrior& Warrior::operator=(const Warrior& src){
            if (this != &src) {
                Character::operator=(src);
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
                // Level was read by nothing before this: a level 9 character
                // hit exactly as hard as a level 1 with the same skills.
                return dmg + getLevel();
        }
        void Warrior::display(std::ostream& os) const{
            Character::display(os);

            for (int i = 0; i < m_skillCount; i++){

            os << "Skill" << i + 1  << ": " << m_skillLevels[i] << "\n";
            
        }
    }

        // Emits exactly what Arena::load() parses:
        //   Warrior,name,health,level,count,skill...
        void Warrior::save(std::ostream& os) const{
            os << "Warrior,";
            saveBase(os);
            os << "," << m_skillCount;
            for (int i = 0; i < m_skillCount; i++){
                os << "," << m_skillLevels[i];
            }
            os << "\n";
        }
}
