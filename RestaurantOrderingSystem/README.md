# Restaurant Ordering System

A command-line restaurant ordering app in C++: browse a menu loaded from CSV, build a bill, and get a total with tax.

## Design

- `Billable` is an abstract base class — anything that can go on a bill implements it.
- `Food` and `Drink` extend `Billable` with their own attributes (sizes for drinks, customizations for food).
- `Menu` and `MenuItem` drive the interactive CLI, built to nest menus without duplicating navigation code.
- `Ordering` is the entry point that ties loading, menu display, and billing together.
- `Utils` holds shared string and input-handling helpers.

## Build and run

```bash
cd RestaurantOrderingSystem
g++ *.cpp -o RestaurantOrderingSystem
./RestaurantOrderingSystem
```

It reads menu items from `drinks.csv` and `foods.csv` in the same directory, then presents the ordering menu.

## Files

- `Billable.h/cpp` — base class for anything orderable
- `Food.h/cpp`, `Drink.h/cpp` — concrete menu item types
- `Ordering.h/cpp` — order and billing logic
- `Menu.h/cpp` — CLI menu system
- `Utils.h/cpp` — helpers
- `constants.h` — shared constants
- `*.csv` — sample menu data
