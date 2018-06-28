#pragma once

#include "page.h"

namespace batup {

    /**
     * decompressor interface
     */
    class decompressor {
    public:
        virtual ~decompressor() = default;
        
        /**
         * decompress data found in indexedPage into page
         *
         * @param indexedPage - the input indexed page
         * @param page - the decompressed page
         */
        virtual void decompress(const IndexedPage &indexedPage, Page &page) = 0;
    };

}
