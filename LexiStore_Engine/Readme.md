# LexiStore Engine

A key-value store written from scratch in C++, without `std::string`, `std::vector`, or any other STL container.

## Design

- `Entry` holds one key-value pair, with its own deep-copy logic for the strings it owns.
- `KVStore` manages a dynamic collection of `Entry` objects, including a custom `operator+=` that reallocates and grows the backing array as entries are added.
- `Utils` holds shared input-sanitizing helpers so bad input doesn't crash the program.
- Every resource-owning class implements the Rule of Three (destructor, copy constructor, copy assignment) by hand.

## Why

Built to work through deep-copy vs. shallow-copy bugs and manual array growth directly, instead of relying on containers that handle it for you.

## Build and run

```bash
cd LexiStore_Engine
g++ *.cpp -o lexistore
./lexistore
```
