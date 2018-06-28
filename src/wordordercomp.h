#pragma once

#include "compressor.h"

namespace batup {

    /**
     * a word order compressor that takes advantage of common data words in
     * a data file to reduce storage size
     * 
     * file of sequence:
     *
     * A1
     * A2
     * A1
     * A3
     *
     * is compressed to
     *
     * data: offset
     * A1: 0, 2
     * A2: 1
     * A3: 3
     *
     */
    class wordordercomp : public compressor {
    public:
        void compress(const Page &page, IndexedPage &indexedPage) override;
    };
}
