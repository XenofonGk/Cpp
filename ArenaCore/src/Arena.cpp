#include "Arena.h"
#include <fstream>
#include <sstream>
#include <string>

namespace GameArena {

    Arena::Arena() {
        m_roster = nullptr;
        m_count = 0;
    }

    // The Arena owns every character it holds, so it deletes them here. Deleting
    // through the Character* base is only safe because iCombatant declares a
    // virtual destructor.
    Arena::~Arena() {
        for (int i = 0; i < m_count; i++) {
            delete m_roster[i];
        }
        delete[] m_roster;
        m_roster = nullptr;
        m_count = 0;
    }

    int Arena::size() const {
        return m_count;
    }

    Character* Arena::getCharacter(int index) const {
        if (index < 0 || index >= m_count) {
            return nullptr;
        }
        return m_roster[index];
    }

    // Grows the roster by one and takes ownership of the incoming character.
    Arena& Arena::operator+=(Character* combatant) {
        if (combatant == nullptr) {
            return *this;
        }

        Character** expanded = new Character*[m_count + 1];
        for (int i = 0; i < m_count; i++) {
            expanded[i] = m_roster[i];
        }
        expanded[m_count] = combatant;

        delete[] m_roster;
        m_roster = expanded;
        m_count++;

        return *this;
    }

    /*
     * Reads a roster file of the form:
     *
     *   Warrior,Aragorn,120,5,3,10,20,15
     *   Mage,Gandalf,80,8,3,40,35,50
     *
     * That is: type, name, health, level, skill count, then that many skills.
     * A malformed line is reported and skipped rather than aborting, so one bad
     * row cannot cost the whole roster.
     */
    void Arena::load(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open " << filename << " for reading.\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            std::istringstream row(line);
            std::string type;
            std::string name;
            std::string field;

            int health = 0, level = 0, count = 0;

            // stoi throws on anything non-numeric. Without this the comment
            // above was a lie: a single malformed digit anywhere in the file
            // propagated out of load() and took the whole roster with it.
            try {
                if (!std::getline(row, type, ',')) continue;
                if (!std::getline(row, name, ',')) continue;

                if (!std::getline(row, field, ',')) continue;
                health = std::stoi(field);

                if (!std::getline(row, field, ',')) continue;
                level = std::stoi(field);

                if (!std::getline(row, field, ',')) continue;
                count = std::stoi(field);
            } catch (const std::exception&) {
                std::cerr << "Skipping unparseable line: " << line << "\n";
                continue;
            }

            if (count < 0) continue;

            int* skills = new int[count];
            bool complete = true;
            for (int i = 0; i < count; i++) {
                if (!std::getline(row, field, ',')) {
                    complete = false;
                    break;
                }
                try {
                    skills[i] = std::stoi(field);
                } catch (const std::exception&) {
                    complete = false;
                    break;
                }
            }

            if (!complete) {
                std::cerr << "Skipping malformed line: " << line << "\n";
                delete[] skills;
                continue;
            }

            if (type == "Warrior") {
                *this += new Warrior(name.c_str(), health, level, skills, count);
            } else if (type == "Mage") {
                *this += new Mage(name.c_str(), health, level, skills, count);
            } else {
                std::cerr << "Unknown character type: " << type << "\n";
            }

            // Warrior and Mage each copy the skill array into their own storage,
            // so this temporary is ours to release either way.
            delete[] skills;
        }
    }

    // Writes the roster back in exactly the format load() reads, so a save/load
    // round trip is lossless. Which line gets written is decided by the object
    // itself through the virtual save().
    void Arena::save(const char* filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Could not open " << filename << " for writing.\n";
            return;
        }

        for (int i = 0; i < m_count; i++) {
            if (m_roster[i] != nullptr) {
                m_roster[i]->save(file);
            }
        }
    }

    void Arena::display(std::ostream& os) const {
        if (m_count == 0) {
            os << "The arena is empty.\n";
            return;
        }

        for (int i = 0; i < m_count; i++) {
            os << "[" << i << "] ";
            m_roster[i]->display(os);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Character& c) {
        c.display(os);
        return os;
    }
}
