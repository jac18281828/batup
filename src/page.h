#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

namespace batup {

    // TYPES
    
    using magic_t = uint32_t;
    using filesz_t = uint64_t;

    const magic_t MAGIC = 0xdeadbeef;
    
    using pagesz_t = uint16_t;
    using word_t    = uint32_t;


    // GLOBAL definitions
    
    const word_t PAGE_SIZE = 256*1024;
    const word_t PAGE_WORDS = PAGE_SIZE/sizeof(word_t);

    // a page of binary data
    typedef struct Page {
        size_t size;
        word_t buffer[PAGE_WORDS];

        Page() : size(0UL) {}
        Page(size_t size) : size(size) {}
    } Page;

    // an index of words mapping to offsets
    using IndexedPage = std::unordered_map<word_t, std::vector<pagesz_t>>;
}
