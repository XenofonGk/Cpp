#include <iostream>
#include <cstring>
#include "../include/Island.h"

namespace Ikariam {

    Island::Island(const char* name,int capacity){
        if (name != nullptr) {
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);

        } else { 
            m_name = nullptr; 
        }

        m_capacity = capacity;
        m_count = 0;

        m_buildings = new Building*[m_capacity];
        for (int i=0; i<m_capacity; i++){
            m_buildings[i] = nullptr;
        }
    }

    Island::~Island(){
        delete[] m_name;
        for (int i = 0; i<m_count; i++) {
            delete m_buildings[i];
        }
        delete[] m_buildings;
    }

    Island::Island(const Island& src){
        m_capacity = src.m_capacity;
        m_count = src.m_count;

        if (src.m_name != nullptr){
        m_name = new char[strlen(src.m_name) + 1];
        strcpy(m_name, src.m_name);
        } else {
            m_name = nullptr;
        }

        if (src.m_buildings != nullptr) {
            m_buildings = new Building*[m_capacity];
            for ( int i = 0; i < m_count; i++){
               m_buildings[i] = src.m_buildings[i]->clone();
            }
        }
    }

    Island& Island::operator=(const Island& src){
        if (this != &src){

        delete[] m_name;
        for (int i = 0; i<m_count; i++) {
            delete m_buildings[i];
        }
        delete[] m_buildings;    

        m_capacity = src.m_capacity;
        m_count = src.m_count;

        if (src.m_name != nullptr){
        m_name = new char[strlen(src.m_name) + 1];
        strcpy(m_name, src.m_name);
        } else {
            m_name = nullptr;
        }

        if (m_buildings != nullptr) {
            m_buildings = new Building*[m_capacity];
            for ( int i = 0; i < m_count; i++){
                m_buildings[i] = src.m_buildings[i]->clone();
            }
        }
        }
        return *this;
    }

    void Island::addBuilding(const Building& b){
        if (m_count < m_capacity ){
            m_buildings[m_count] = b.clone();
            m_count++;
        }
    }

    void Island::display(std::ostream& os) const{
        if (m_name) {
            os << "Island: " << m_name << std::endl;
        }
        for (int i = 0; i < m_count; i++) {
            os << (i + 1) << ": " << *m_buildings[i] << std::endl;
        }
    }

}