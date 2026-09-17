# CreditCard

A small class that validates and formats credit card records — name, number, CVV, and expiry — and rejects malformed ones instead of displaying them.

## What it demonstrates

- `CC` validates on construction and on `set()`: a name that's too short, a bad expiry month, or other malformed input results in `isEmpty()` and a display that just prints "Invalid Credit Card Record" instead of garbage data.
- The name is heap-allocated and deep-copied (own `aloCopy`/`cleanUp` helpers), formatted to a fixed width for display.
- Card numbers print grouped in blocks of 4 (`4098 7654 2345 7896`) rather than as one long digit string.

## Build and run

```bash
cd CreditCard
g++ *.cpp -o creditcard
./creditcard
```
