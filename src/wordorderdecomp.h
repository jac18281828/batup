#pragma once

#include "decompressor.h"

namespace batup {

    /**
     * merge the indexed page into a page buffer
     */
    class wordorderdecomp : public decompressor {
    public:
        void decompress(const IndexedPage &indexedPage,  Page &page) override;
    };
}
