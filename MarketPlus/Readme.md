# MarketPlus

A small C++ shopping cart engine that simulates e-commerce inventory logic without any standard library containers.

## What it demonstrates

- Manual memory management — `Cart` and `Item` allocate and free their own strings and arrays with `new`/`delete`, including deep copies so no two objects share the same buffer.
- A `Cart` that grows its own backing array when full, the same resizing idea `std::vector` uses internally, written by hand.
- Operator overloading for a natural-reading API: `cart += item` adds a product, `cart -= sku` removes one by ID, `item += 5` restocks a quantity.
- `friend` classes so `Cart` and `Item` can reach into each other's private state without opening it up to everything else.

## Build and run

```bash
cd MarketPlus
g++ *.cpp -o marketplus
./marketplus
```
