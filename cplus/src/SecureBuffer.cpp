#include "include/SecureBuffer.hpp"
#include <algorithm>

// Secure memory wipe (prevents compiler optimizations)
void SecureBuffer::secure_wipe(void* ptr, size_t len) noexcept {
    if (!ptr || len == 0) return;
    volatile char* p = reinterpret_cast<volatile char*>(ptr);
    while (len--) {
        *p++ = 0;
    }
}

SecureBuffer::SecureBuffer(size_t s)
    : data(std::make_unique<char[]>(s)), size(s) {
    std::fill(data.get(), data.get() + size, 0);
}

SecureBuffer::SecureBuffer(SecureBuffer&& other) noexcept
    : data(std::move(other.data)), size(other.size) {
    other.size = 0;
}

SecureBuffer& SecureBuffer::operator=(SecureBuffer&& other) noexcept {
    if (this != &other) {
        secure_wipe(data.get(), size);
        data = std::move(other.data);
        size = other.size;
        other.size = 0;
    }
    return *this;
}

SecureBuffer::~SecureBuffer() {
    secure_wipe(data.get(), size);
}

char* SecureBuffer::data_ptr() noexcept {
    return data.get();
}

const char* SecureBuffer::data_ptr() const noexcept {
    return data.get();
}

size_t SecureBuffer::size_bytes() const noexcept {
    return size;
}
