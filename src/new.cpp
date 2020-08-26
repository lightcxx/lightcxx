#include "new"

#include <stdlib.h>

#include "handler.h"

namespace std {

bad_alloc::bad_alloc() noexcept = default;

bad_alloc::bad_alloc(const bad_alloc&) noexcept = default;

bad_alloc& bad_alloc::operator=(const bad_alloc&) noexcept = default;

bad_alloc::~bad_alloc() noexcept = default;

const char* bad_alloc::what() const noexcept {
    return "bad_alloc";
}

bad_array_new_length::bad_array_new_length() noexcept = default;

bad_array_new_length::bad_array_new_length(const bad_array_new_length&) noexcept = default;

bad_array_new_length&
  bad_array_new_length::operator=(const bad_array_new_length&) noexcept = default;

bad_array_new_length::~bad_array_new_length() noexcept = default;

const char* bad_array_new_length::what() const noexcept {
    return "bad_array_new_length";
}

const nothrow_t nothrow;

namespace {
_Light::Handler<new_handler> global_new_handler;
}

new_handler get_new_handler() noexcept {
    return global_new_handler.get();
}

new_handler set_new_handler(new_handler handler) noexcept {
    return global_new_handler.set(handler);
}

}  // namespace std

// Single-object forms

__attribute__((__weak__)) void* operator new(std::size_t size) {
    if (size == 0) {
        size = 1;
    }
    void* ptr;
    for (ptr = ::malloc(size); ptr == nullptr; ptr = ::malloc(size)) {
        const auto handler = std::get_new_handler();
        if (handler) {
            handler();
        } else {
            throw std::bad_alloc();
        }
    }
    return ptr;
}

__attribute__((__weak__)) void* operator new(std::size_t size, std::align_val_t given_alignment) {
    if (size == 0) {
        size = 1;
    }
    auto align = static_cast<size_t>(given_alignment);
    void* ptr;
    for (ptr = ::aligned_alloc(align, size); ptr == nullptr; ptr = ::aligned_alloc(align, size)) {
        const auto handler = std::get_new_handler();
        if (handler) {
            handler();
        } else {
            throw std::bad_alloc();
        }
    }
    return ptr;
}

__attribute__((__weak__)) void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
    void* ptr = nullptr;
    try {
        ptr = ::operator new(size);
    } catch (...) {}
    return ptr;
}

__attribute__((__weak__)) void*
  operator new(size_t size, std::align_val_t align, const std::nothrow_t&) noexcept {
    void* p = nullptr;
    try {
        p = ::operator new(size, align);
    } catch (...) {}
    return p;
}

__attribute__((__weak__)) void operator delete(void* ptr) noexcept {
    ::free(ptr);
}

__attribute__((__weak__)) void operator delete(void* ptr, size_t) noexcept {
    ::operator delete(ptr);
}

__attribute__((__weak__)) void operator delete(void* ptr, std::align_val_t) noexcept {
    ::operator delete(ptr);
}

__attribute__((__weak__)) void operator delete(void* ptr, size_t, std::align_val_t align) noexcept {
    ::operator delete(ptr, align);
}

__attribute__((__weak__)) void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    ::operator delete(ptr);
}

__attribute__((__weak__)) void
  operator delete(void* ptr, std::align_val_t align, const std::nothrow_t&) noexcept {
    ::operator delete(ptr, align);
}

// Array forms

__attribute__((__weak__)) void* operator new[](std::size_t size) {
    return ::operator new(size);
}

__attribute__((__weak__)) void* operator new[](size_t size, std::align_val_t align) {
    return ::operator new(size, align);
}

__attribute__((__weak__)) void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    void* ptr = nullptr;
    try {
        ptr = ::operator new[](size);
    } catch (...) {}
    return ptr;
}

__attribute__((__weak__)) void*
  operator new[](size_t size, std::align_val_t align, const std::nothrow_t&) noexcept {
    void* p = nullptr;
    try {
        p = ::operator new[](size, align);
    } catch (...) {}
    return p;
}

__attribute__((__weak__)) void operator delete[](void* ptr) noexcept {
    ::operator delete(ptr);
}

__attribute__((__weak__)) void operator delete[](void* ptr, size_t) noexcept {
    ::operator delete[](ptr);
}

__attribute__((__weak__)) void operator delete[](void* ptr, std::align_val_t align) noexcept {
    ::operator delete(ptr, align);
}

__attribute__((__weak__)) void
  operator delete[](void* ptr, size_t, std::align_val_t align) noexcept {
    ::operator delete[](ptr, align);
}

__attribute__((__weak__)) void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
    ::operator delete[](ptr);
}

__attribute__((__weak__)) void
  operator delete[](void* ptr, std::align_val_t align, const std::nothrow_t&) noexcept {
    ::operator delete[](ptr, align);
}

// Non-allocating forms

void* operator new(std::size_t, void* ptr) noexcept {
    return ptr;
}

void* operator new[](std::size_t, void* ptr) noexcept {
    return ptr;
}

void operator delete(void*, void*) noexcept {}

void operator delete[](void*, void*) noexcept {}
