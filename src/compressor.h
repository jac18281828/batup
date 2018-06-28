#pragma once

#include "page.h"

namespace batup {

    /**
     * compressor interface
     */
    class compressor {
    public:
        virtual ~compressor() = default;

        /**
         * Compress data found in page into indexedPage
         *
         * @param page - the input page
         * @param indexedPage - the resulting indexed data after compression
         *
         */
        virtual void compress(const Page &page, IndexedPage &indexedPage) = 0;
    };
}
