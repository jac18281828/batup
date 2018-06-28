#pragma once

#include "app.h"
#include "properties.h"
#include "decompressor.h"

namespace batup {
    
    class decompapp final : public app {
    private:
        decompressor *decomp;

        /*
         * read the batup header
         */
        bool readheader(std::istream &in, filesz_t &fileSize);

        /*
         * read a compressed index page
         */
        void readidx(std::istream &in, IndexedPage &page) const;

        /*
         * write a data page
         */
        filesz_t writepage(std::ostream &out, Page &page, filesz_t nWritten, filesz_t fileSize) const;
    protected:
        /* 
         * process using the given streams
         */
        void process(std::istream &in, std::ostream &out);
    public:
        decompapp(const properties &props, decompressor *decomp);
    };
}
