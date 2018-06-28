#pragma once

#include <iostream>

#include "app.h"
#include "properties.h"
#include "compressor.h"

namespace batup {

    class compapp final : public app {
    private:
        compressor *comp;

        /*
         * write the batup header
         */
        void writeheader(std::ostream &out, filesz_t fileSize) const;

        /*
         * read a page of binary data
         */
        size_t readpage(std::istream &in, Page &page) const;

        /*
         * write the indexed compact data
         */
        void writeidx(std::ostream &out, IndexedPage &indPage) const;
    protected:

        /* 
         * process using the given streams
         */
        void process(std::istream &in, std::ostream &out);
    public:
        compapp(const properties &props, compressor *comp);
    };
}
