// Regression tests for ArenaCore.
//
// Built with -fsanitize=address in CI, because the bug that prompted this file
// was a memory error rather than a wrong answer: Mage::operator+= incremented
// the array pointer instead of the element count, so the spell never counted
// and the destructor freed a pointer that was not the start of the allocation.
// A correctness-only test would have caught half of that; ASan catches the rest.

#include "Arena.h"
#include "Warrior.h"
#include "Mage.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace GameArena;

namespace {

int g_failures = 0;

void check(bool condition, const std::string& what) {
    if (condition) {
        std::cout << "  ok   " << what << "\n";
    } else {
        std::cout << "  FAIL " << what << "\n";
        g_failures++;
    }
}

void checkEq(int actual, int expected, const std::string& what) {
    check(actual == expected, what + " (expected " + std::to_string(expected) +
                                  ", got " + std::to_string(actual) + ")");
}

/* Adding a spell must raise damage by exactly that spell's value, and the
   object must destruct cleanly. Before the fix this failed twice over: damage
   did not change, and the destructor freed a mid-allocation pointer. */
void mageAddSpellCounts() {
    int power[] = {40, 35, 50};
    Mage m("Gandalf", 80, 8, power, 3);

    const int before = m.calculateDamage();
    m += 10;
    const int after = m.calculateDamage();

    checkEq(after - before, 10, "Mage += raises damage by the spell value");
}

void warriorAddSkillCounts() {
    int skills[] = {10, 20, 15};
    Warrior w("Aragorn", 120, 5, skills, 3);

    const int before = w.calculateDamage();
    w += 7;
    checkEq(w.calculateDamage() - before, 7, "Warrior += raises damage by the skill value");
}

/* Repeated appends are where a corrupted pointer compounds. */
void repeatedAppendsAreStable() {
    int power[] = {5};
    Mage m("Test", 50, 1, power, 1);

    int expected = m.calculateDamage();
    for (int i = 1; i <= 20; i++) {
        m += i;
        expected += i;
    }
    checkEq(m.calculateDamage(), expected, "20 successive appends stay consistent");
}

/* m_name is a fixed 50 bytes and the source is a file, so an over-long name
   must be truncated rather than written past the end. */
void longNameIsTruncated() {
    const std::string huge(300, 'A');
    Warrior w(huge.c_str(), 100, 1, nullptr, 0);
    check(std::strlen(w.getName()) < 50, "over-long name is truncated, not overflowed");
}

/* A single bad field used to throw out of load() and lose the whole roster. */
void malformedRosterLineIsSkipped() {
    const char* path = "test_roster_malformed.txt";
    {
        std::ofstream f(path);
        f << "Warrior,Good,100,1,1,10\n"
          << "Warrior,Bad,notanumber,1,1,10\n"
          << "Mage,AlsoGood,80,2,1,20\n";
    }

    Arena arena;
    arena.load(path);
    checkEq(arena.size(), 2, "malformed line skipped, valid ones still loaded");
    std::remove(path);
}

/* Identity includes the name; comparing only stats made unrelated characters
   compare equal. */
void equalityConsidersName() {
    int s[] = {10};
    Warrior a("Aragorn", 100, 5, s, 1);
    Warrior b("Boromir", 100, 5, s, 1);
    Warrior c("Aragorn", 100, 5, s, 1);

    check(!(static_cast<Character&>(a) == static_cast<Character&>(b)),
          "different names are not equal");
    check(static_cast<Character&>(a) == static_cast<Character&>(c),
          "same name and stats are equal");
}

/* The Arena owns its roster; ASan reports any double free or leak here. */
void arenaOwnsAndFreesRoster() {
    int s[] = {10, 20};
    int p[] = {30};
    {
        Arena arena;
        arena += new Warrior("W", 100, 1, s, 2);
        arena += new Mage("M", 80, 2, p, 1);
        checkEq(arena.size(), 2, "roster holds both combatants");
        check(arena.getCharacter(5) == nullptr, "out-of-range index returns nullptr");
    }
    check(true, "arena destructed without a memory error");
}

} // namespace

int main() {
    std::cout << "ArenaCore tests\n";
    mageAddSpellCounts();
    warriorAddSkillCounts();
    repeatedAppendsAreStable();
    longNameIsTruncated();
    malformedRosterLineIsSkipped();
    equalityConsidersName();
    arenaOwnsAndFreesRoster();

    std::cout << (g_failures == 0 ? "\nall passed\n"
                                  : "\n" + std::to_string(g_failures) + " failed\n");
    return g_failures == 0 ? 0 : 1;
}
