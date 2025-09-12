#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef> // for std::byte

// RAII Secure Buffer
class SecureBuffer {
private:
    std::unique_ptr<char[]> data;
    size_t size;

    static void secure_wipe(void* ptr, size_t len) noexcept {
        if (!ptr || len == 0) return;
        volatile char* p = reinterpret_cast<volatile char*>(ptr);
        while (len--) {
            *p++ = 0;
        }
    }

public:
    explicit SecureBuffer(size_t s)
        : data(std::make_unique<char[]>(s)), size(s) {
        std::fill(data.get(), data.get() + size, 0);
    }

    // Disable copying
    SecureBuffer(const SecureBuffer&) = delete;
    SecureBuffer& operator=(const SecureBuffer&) = delete;

    // Enable moving
    SecureBuffer(SecureBuffer&& other) noexcept
        : data(std::move(other.data)), size(other.size) {
        other.size = 0;
    }

    SecureBuffer& operator=(SecureBuffer&& other) noexcept {
        if (this != &other) {
            // wipe current memory before overwriting
            secure_wipe(data.get(), size);
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    ~SecureBuffer() {
        secure_wipe(data.get(), size);
    }

    // Accessors
    char* data_ptr() noexcept { return data.get(); }
    const char* data_ptr() const noexcept { return data.get(); }
    size_t size_bytes() const noexcept { return size; }
};
