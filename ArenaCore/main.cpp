#include "Arena.h"
#include "Input.h"
#include <iostream>

/*
 * Entry point for ArenaCore.
 *
 * All console interaction lives here and in src/input.cpp. Arena, Character,
 * Warrior and Mage contain no reads from stdin, which keeps the model testable
 * and independent of how it is driven.
 */

using namespace GameArena;

namespace {

    void showMenu() {
        std::cout << "\n=== ArenaCore ===\n"
                  << "1. Display roster\n"
                  << "2. Attack with a character\n"
                  << "3. Level up a character\n"
                  << "4. Add a skill to a character\n"
                  << "5. Save roster\n"
                  << "0. Quit\n";
    }

    // Prompts for a roster index, or returns nullptr when the arena is empty.
    Character* pickCharacter(const Arena& arena) {
        if (arena.size() == 0) {
            std::cout << "The roster is empty.\n";
            return nullptr;
        }
        std::cout << "Choose a character [0-" << arena.size() - 1 << "]\n";
        int index = readInt(0, arena.size() - 1);
        return arena.getCharacter(index);
    }
}

int main() {
    Arena arena;
    arena.load("roster.txt");

    std::cout << "Loaded " << arena.size() << " characters.\n";

    bool running = true;
    while (running) {
        showMenu();
        int choice = readInt(0, 5);

        switch (choice) {
        case 1:
            arena.display(std::cout);
            break;

        case 2: {
            Character* c = pickCharacter(arena);
            if (c != nullptr) {
                // attack() is resolved through the iCombatant interface, so a
                // Warrior sums skills and a Mage sums spell power without the
                // caller knowing which it holds.
                std::cout << "Damage dealt: " << c->attack() << "\n";
            }
            break;
        }

        case 3: {
            Character* c = pickCharacter(arena);
            if (c != nullptr) {
                ++(*c);
                std::cout << "Levelled up:\n" << *c;
            }
            break;
        }

        case 4: {
            Character* c = pickCharacter(arena);
            if (c != nullptr) {
                std::cout << "Skill value [1-100]\n";
                int value = readInt(1, 100);
                // += is declared on the concrete types, so the roster has to be
                // narrowed before the skill can be appended.
                if (Warrior* w = dynamic_cast<Warrior*>(c)) {
                    *w += value;
                } else if (Mage* m = dynamic_cast<Mage*>(c)) {
                    *m += value;
                }
                std::cout << *c;
            }
            break;
        }

        case 5:
            arena.save("roster-out.txt");
            std::cout << "Saved to roster-out.txt\n";
            break;

        case 0:
            running = false;
            break;
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
