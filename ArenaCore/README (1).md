# ArenaCore — C++ Combat Character Engine

A text-based RPG combat system built in C++ demonstrating core Object-Oriented Programming concepts including manual memory management, polymorphism, operator overloading, and file I/O.

## Concepts Demonstrated

| Concept | Where |
|---|---|
| Modular `.h` / `.cpp`, `namespace` | Every file |
| Function overloading | `Character` constructors |
| `new[]` / `delete[]` (DMA) | `Warrior`, `Mage` |
| Constructors & destructors | All classes |
| `this` pointer, pass by reference | Copy constructors, assignment |
| `operator+=` (binary member) | `Warrior`, `Mage` — adds skill/spell |
| `operator++` prefix & postfix | `Character`, `Warrior`, `Mage` |
| `operator bool()` | `Character` — true if alive |
| Single-arg cast constructor | `Character(int level)` |
| `*this = ctor()` localizing pattern | `Warrior`, `Mage` default ctors |
| Free helper `operator<<` / `>>` | `Character` stream operators |
| `friend` operator | `operator==` in `Character` |
| Rule of Three | `Warrior`, `Mage` (full deep copy) |
| File I/O (`ifstream` / `ofstream`) | `Arena::load()`, `Arena::save()` |
| Robust input validation | `input::readInt()` |
| Inheritance + calling base ctor | `Character → Warrior / Mage` |
| `virtual` functions | `Character::display()` |
| `virtual` destructor | `~Character()` |
| Abstract class + pure virtual | `Character::calculateDamage() = 0` |
| Pure interface class | `iCombatant` |
| Rule of Three in derived class | `Warrior`, `Mage` call `Character(src)` |

## Project Structure

```
ArenaCore/
├── CMakeLists.txt
├── main.cpp
├── include/
│   └── ArenaCore/
│       ├── iCombatant.h
│       ├── Character.h
│       ├── Warrior.h
│       ├── Mage.h
│       ├── Arena.h
│       └── input.h
├── src/
│   ├── input.cpp
│   ├── Character.cpp
│   ├── Warrior.cpp
│   ├── Mage.cpp
│   └── Arena.cpp
└── data/
    └── roster.txt
```

## Build Instructions

```bash
mkdir build && cd build
cmake ..
cmake --build .
./ArenaCore
```

## How It Works

- Characters are loaded from `roster.txt` into an `Arena` object
- The Arena holds a polymorphic array of `Character*` pointers
- Warrior damage = sum of all skill levels
- Mage damage = product of all spell powers
- Characters can level up (`++`), gain health (`+=`), and be compared (`==`)
- The roster persists between sessions via file save/load

## roster.txt Format

```
Type,Name,Health,Level,SkillCount,skill1,skill2,...
```

Example:
```
Warrior,Aragorn,120,5,3,10,20,15
Mage,Gandalf,80,8,3,40,35,50
```
