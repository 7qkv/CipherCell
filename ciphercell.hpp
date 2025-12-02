/*
 * MIT License
 * Copyright (c) 2025 qn
 */
#ifndef CIPHERCELL_HPP
#define CIPHERCELL_HPP

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace cc {
    constexpr uint64_t hash(const char* s, uint64_t h = 0xcbf29ce484222325ULL) {
        return *s ? hash(s + 1, (h ^ *s) * 0x100000001b3ULL) : h;
    }
    
    constexpr uint64_t seed(int c) {
        return hash(__DATE__ __TIME__) + c * 0x9e3779b97f4a7c15ULL;
    }
    
    template<typename T>
    struct alignas(T) EncryptedStorage {
        uint8_t data[sizeof(T)];
        uint64_t key;
        
        constexpr EncryptedStorage() : data{}, key(seed(__COUNTER__)) {}
        
        void store(const T& value) {
            const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
            const uint8_t* k = reinterpret_cast<const uint8_t*>(&key);
            for(size_t i = 0; i < sizeof(T); ++i) {
                data[i] = src[i] ^ k[i % sizeof(key)] ^ (uint8_t)(key >> ((i * 7) % 64));
            }
        }
        
        T load() const {
            T result;
            uint8_t* dst = reinterpret_cast<uint8_t*>(&result);
            const uint8_t* k = reinterpret_cast<const uint8_t*>(&key);
            for(size_t i = 0; i < sizeof(T); ++i) {
                dst[i] = data[i] ^ k[i % sizeof(key)] ^ (uint8_t)(key >> ((i * 7) % 64));
            }
            return result;
        }
    };
}

template<typename T>
class CipherCell {
    static_assert(std::is_trivially_copyable<T>::value, "Type must be trivially copyable");
    
    cc::EncryptedStorage<T> storage;
    
public:
    CipherCell() { storage.store(T{}); }
    
    explicit CipherCell(const T& value) { storage.store(value); }
    
    CipherCell& operator=(const T& value) {
        storage.store(value);
        return *this;
    }
    
    T get() const { return storage.load(); }
    
    operator T() const { return storage.load(); }
    
    CipherCell& operator+=(const T& rhs) { storage.store(storage.load() + rhs); return *this; }
    CipherCell& operator-=(const T& rhs) { storage.store(storage.load() - rhs); return *this; }
    CipherCell& operator*=(const T& rhs) { storage.store(storage.load() * rhs); return *this; }
    CipherCell& operator/=(const T& rhs) { storage.store(storage.load() / rhs); return *this; }
    
    CipherCell& operator++() { storage.store(storage.load() + 1); return *this; }
    CipherCell& operator--() { storage.store(storage.load() - 1); return *this; }
    T operator++(int) { T tmp = storage.load(); storage.store(tmp + 1); return tmp; }
    T operator--(int) { T tmp = storage.load(); storage.store(tmp - 1); return tmp; }
};

#endif