# Cpp

C++ projects from my OOP coursework, each built around a different core idea — abstract interfaces, the Rule of Three, operator overloading, manual memory management. No STL containers anywhere; the point of these was to write the mechanics by hand.

Each project is self-contained and has its own README with more detail. Compile with any C++ compiler that supports C++11 or later (I use `g++` below); commands assume you're in the `Cpp/` directory.

## Projects

**[ArenaCore](ArenaCore)** — a turn-based combat engine built on top of the original coursework object model, with an added combat system, a test suite, and a WebAssembly build. The most complete project in this repo; see its own README for build steps (CMake wasn't available in the environment I verified the rest of this repo from, so I didn't re-test it here).

**[Ikariam](Ikariam)** — a building-simulation engine inspired by the browser game, with an abstract `Building` base class and a clone pattern for managing buildings on an `Island`.
```bash
cd Ikariam/src && g++ -I../include *.cpp -o ikariam && ./ikariam
```

**[Sorting](Sorting)** — five sorting algorithms (selection, bubble, insertion, quick, merge) behind a common `iSorter` interface, instantiated through a factory function.
```bash
cd Sorting && g++ Sorter.cpp main.cpp -o sorting && ./sorting
```

**[RestaurantOrderingSystem](RestaurantOrderingSystem)** — a CLI ordering system that loads a menu from CSV and generates a bill.
```bash
cd RestaurantOrderingSystem && g++ *.cpp -o RestaurantOrderingSystem && ./RestaurantOrderingSystem
```

**[MarketPlus](MarketPlus)** — a shopping-cart engine with operator overloading (`cart += item`) and a `Cart` that grows its own backing array.
```bash
cd MarketPlus && g++ *.cpp -o marketplus && ./marketplus
```

**[CreditCard](CreditCard)** — validates card numbers and manages credit limits.
```bash
cd CreditCard && g++ *.cpp -o creditcard && ./creditcard
```

**[LexiStore_Engine](LexiStore_Engine)** — a key-value store built without any STL containers, including a hand-rolled resizing array.
```bash
cd LexiStore_Engine && g++ *.cpp -o lexistore && ./lexistore
```

---
*Xenofon Gkioka*
