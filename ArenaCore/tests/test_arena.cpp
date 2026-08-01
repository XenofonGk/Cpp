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
#include <sstream>
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


/* ---- combat ---------------------------------------------------------- */

void levelAffectsDamage() {
    int skills[] = {10, 10};
    Warrior low("Low", 100, 1, skills, 2);
    Warrior high("High", 100, 9, skills, 2);
    check(high.calculateDamage() > low.calculateDamage(),
          "a higher level hits harder with identical skills");
    checkEq(high.calculateDamage() - low.calculateDamage(), 8,
            "the damage gap equals the level gap");
}

void defenceReducesDamageTaken() {
    int s[] = {30};
    Warrior attacker("A", 100, 1, s, 1);
    Warrior soft("Soft", 100, 0, s, 1);   // defence 0
    Warrior armoured("Hard", 100, 8, s, 1); // defence 4

    Character::seedCombat(1);
    const int toSoft = attacker.strike(soft);
    Character::seedCombat(1);
    const int toArmoured = attacker.strike(armoured);

    checkEq(toSoft - toArmoured, 4, "defence subtracts from the damage taken");
}

void damageNeverDropsBelowOne() {
    int weak[] = {1};
    int s[] = {1};
    Warrior attacker("Weak", 100, 0, weak, 1);
    Warrior tank("Tank", 100, 99, s, 1);   // defence 49, far above the damage
    const int dealt = attacker.strike(tank);
    check(dealt >= 1, "a hit always removes at least one health");
}

void healthClampsAtZero() {
    int s[] = {500};
    Warrior big("Big", 100, 1, s, 1);
    Warrior small("Small", 10, 0, s, 1);
    big.strike(small);
    checkEq(small.getHealth(), 0, "health stops at zero rather than going negative");
    check(!small.isAlive(), "a combatant at zero health is not alive");
}

void healingCannotExceedStartingHealth() {
    int s[] = {5};
    Warrior w("W", 100, 1, s, 1);
    w += -40;
    w += 999;
    checkEq(w.getHealth(), 100, "healing is capped at starting health");
}

void deadCombatantsDoNotSwing() {
    int s[] = {20};
    Warrior dead("Dead", 1, 1, s, 1);
    Warrior alive("Alive", 100, 1, s, 1);
    dead.takeDamage(50);
    checkEq(dead.getHealth(), 0, "the combatant is down");
    checkEq(dead.strike(alive), 0, "a downed combatant deals no damage");
    checkEq(alive.getHealth(), 100, "and the target is untouched");
}

/* Warrior and Mage declare operator+=(int) to append a skill, which HIDES
   Character::operator+=(int) that adjusts health. The same expression therefore
   means two different things depending on the static type of the left operand,
   which is a trap worth pinning down rather than discovering later:
   takeDamage() is the unambiguous way to change health. */
void plusEqualsMeansSkillOnConcreteTypes() {
    int s[] = {10};
    Warrior w("W", 100, 1, s, 1);

    const int damageBefore = w.calculateDamage();
    w += 5;                       // Warrior::operator+= — appends a skill
    checkEq(w.getHealth(), 100, "+= on a Warrior leaves health alone");
    checkEq(w.calculateDamage() - damageBefore, 5, "+= on a Warrior adds a skill");

    Character& asBase = w;
    asBase += -30;                // Character::operator+= — changes health
    checkEq(asBase.getHealth(), 70, "+= through Character& changes health");
}

void sameSeedReplaysTheSameFight() {
    auto run = [] {
        int s[] = {10, 10};
        int p[] = {12, 12};
        Warrior w("W", 120, 4, s, 2);
        Mage m("M", 90, 6, p, 2);
        Character::seedCombat(2026);
        int total = 0;
        for (int i = 0; i < 5; i++) total += w.strike(m) * 10 + m.strike(w);
        return total;
    };
    checkEq(run(), run(), "the same seed produces an identical exchange");
}

void higherLevelStrikesFirst() {
    int s[] = {10};
    int p[] = {10};
    Arena arena;
    arena += new Warrior("Slow", 200, 2, s, 1);
    arena += new Mage("Quick", 200, 9, p, 1);

    Character::seedCombat(5);
    std::ostringstream out;
    arena.fight(0, 1, out);
    const std::string log = out.str();
    check(log.find("Quick hits Slow") < log.find("Slow hits Quick"),
          "the higher-level combatant lands the first blow");
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

    levelAffectsDamage();
    defenceReducesDamageTaken();
    damageNeverDropsBelowOne();
    healthClampsAtZero();
    healingCannotExceedStartingHealth();
    deadCombatantsDoNotSwing();
    plusEqualsMeansSkillOnConcreteTypes();
    sameSeedReplaysTheSameFight();
    higherLevelStrikesFirst();

    std::cout << (g_failures == 0 ? "\nall passed\n"
                                  : "\n" + std::to_string(g_failures) + " failed\n");
    return g_failures == 0 ? 0 : 1;
}
