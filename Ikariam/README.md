# Ikariam

A small building-simulation engine in C++, inspired by the browser strategy game Ikariam.

## Design

- `Building` is an abstract base class with pure virtual `print()` and `clone()`, so every building type prints and copies itself correctly through a base pointer.
- `Island` owns a dynamic array of `Building*` and manages the buildings placed on it — adding a building clones it onto the heap rather than storing a pointer the caller still owns.
- Copy constructor, assignment operator, and destructor are all hand-written (Rule of Three) since buildings own their own name string on the heap.
- No STL containers — just raw arrays and manual `new`/`delete`.

## Build and run

```bash
cd Ikariam/src
g++ -I../include *.cpp -o ikariam
./ikariam
```
