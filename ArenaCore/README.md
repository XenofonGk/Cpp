# ArenaCore

A small turn-based combat engine in C++, built around an abstract combatant
hierarchy.

**Coursework, extended.** The original assignment covered the object model —
an abstract base, two concrete subclasses, operator overloading, and a container
managing heap memory under the Rule of Three. It had no combat: `attack()` took
no target, nothing applied damage, and a fight could not be staged. The combat
system, the tests, and the WebAssembly build were added afterwards.

## The model

`iCombatant` is the interface. `Character` implements the shared state — name,
health, level — and leaves `calculateDamage()` to its subclasses:

- **`Warrior`** carries a skill array; damage is their sum.
- **`Mage`** carries spell power; damage is their sum plus one.

`Arena` owns a roster of `Character*`. Copying it is `= delete`d rather than
deep-copied: the roster holds polymorphic objects through raw pointers, and
deleting the copy operations keeps ownership unambiguous instead of inventing an
answer to "what does copying an arena mean".

## Combat

- **Damage** is `calculateDamage()` rolled within ±20% and reduced by the
  target's defence, never below 1. Armour blunts a hit; it never makes a
  combatant untouchable.
- **Defence** is derived from level rather than stored, so levelling up makes a
  combatant harder to hurt as well as harder-hitting, and the roster file format
  is unchanged.
- **Level** contributes to damage. It previously contributed to nothing — a
  level 9 character hit exactly as hard as a level 1 with the same skills.
- **Turn order** is by level: the higher level strikes first. This is the one
  place a decision changes an outcome, since levelling a combatant up can flip
  who lands the opening blow.
- **The generator is seedable.** `Character::seedCombat(n)` makes a run
  reproducible, which is what lets tests assert exact numbers and lets the
  browser build replay the same fight as the binary.

The roster ships tuned: across 200 seeded fights, Aragorn beats Gandalf 98 times
and loses 102. A glass cannon against a slower, tougher fighter, decided by the
rolls.

## Build and run

```bash
cmake -B build -S . && cmake --build build
cd build && ./ArenaCore
```

## Tests

```bash
g++ -std=c++17 -I include -fsanitize=address \
  -o arena_tests tests/test_arena.cpp src/*.cpp && ./arena_tests
```

Built with AddressSanitizer in CI, because the bug that prompted these tests was
a memory error rather than a wrong answer: an operator incremented the array
pointer instead of the element count, so the destructor freed a pointer that was
never returned by `new[]`. A correctness check alone would have caught the wrong
damage number and said nothing about the corrupted heap.

## A trap worth knowing

`Warrior` and `Mage` declare `operator+=(int)` to append a skill, which **hides**
`Character::operator+=(int)` that adjusts health. The same expression means
different things depending on the static type of the left operand:

```cpp
Warrior w(...);
w += 5;                    // appends a skill
Character& c = w;
c += -30;                  // removes 30 health
```

`takeDamage()` is the unambiguous way to change health, and there is a test
pinning this behaviour so it is documented rather than rediscovered.
