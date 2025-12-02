# CipherCell
Encrypted memory cells that protect your data from memory scanners.

## What is this
Single header library that keeps sensitive values encrypted in RAM. When scanners like Cheat Engine try to find your data, they only see garbage. Values are decrypted only when you access them.

Works with any trivially copyable type.

## How to use
```cpp
#include "ciphercell.hpp"

CipherCell<int> health(100);
health -= 25;
int hp = health.get();

CipherCell<float> damage(45.5f);
damage *= 1.5f;

struct Player { int gold; int level; };
CipherCell<Player> player({5000, 10});
Player p = player.get();
```

Use `.get()` to read the decrypted value or let implicit conversion handle it. Supports arithmetic operators like `+=`, `-=`, `++`, etc.

## How it works
Uses XOR encryption with a compile-time generated key based on date/time hash. Every cell has its own unique key. The actual value is never stored in plain memory - it's always encrypted. Decryption happens on-demand when you access the value.

## Building
```bash
cl /std:c++17 /O2 example.cpp
g++ -std=c++17 -O2 example.cpp
```

Requires C++17 or newer.

## Files
- `ciphercell.hpp` - the header you need to include
- `example.cpp` - usage examples
- `LICENSE` - MIT
- `README.md` - this file

## Limits
Only works with trivially copyable types (int, float, POD structs, etc). Won't protect against advanced memory forensics or someone who reverses the encryption routine. Just makes basic memory scanning much harder.

The encryption is fast (simple XOR) so performance impact is minimal.

## License
MIT

---
made by [7qkv](https://github.com/7qkv)
