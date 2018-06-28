#include <algorithm>
#include <iostream>

#include "page.h"
#include "byteorder.h"
#include "decompapp.h"
#include "wordorderdecomp.h"

using namespace batup;

decompapp::decompapp(const properties &props, decompressor *decomp) : app(props), decomp(decomp) {

}

void decompapp::process(std::istream &in, std::ostream &out) {

    filesz_t fileSize = 0L;
    filesz_t nWritten = 0L;

    if(readheader(in, fileSize)) {
        while(!in.eof()) {
            IndexedPage inputPage;
            Page        outputPage;

            readidx(in, inputPage);

            decomp->decompress(inputPage, outputPage);

            nWritten += writepage(out, outputPage, nWritten, fileSize);
        }

    } else {
        error("Input file is not batz");
        return;
    }
}

bool decompapp::readheader(std::istream &in, filesz_t &fileSize) {
    magic_t magic;
    filesz_t fileSz;

    in.read(reinterpret_cast<char*>(&magic), sizeof(magic_t));
    in.read(reinterpret_cast<char*>(&fileSz), sizeof(filesz_t));

    if(in && native_endian<magic_t>(magic) == MAGIC) {
        fileSize = native_endian<filesz_t>(fileSz);
        return true;
    } else {
        fileSize = 0L;
        return false;
    }
}


void decompapp::readidx(std::istream &in, IndexedPage &page) const {
    pagesz_t pagewords;
    in.read(reinterpret_cast<char*>(&pagewords), sizeof(pagesz_t));
    pagewords = native_endian<pagesz_t>(pagewords);

    // read so many pages
    for(size_t i=0; i<pagewords; i++) {
        word_t inword;
        in.read(reinterpret_cast<char*>(&inword), sizeof(word_t));
        inword = native_endian<word_t>(inword);
        std::vector<pagesz_t> offlist;

        // list len
        pagesz_t qty;
        in.read(reinterpret_cast<char*>(&qty), sizeof(pagesz_t));
        qty = native_endian<pagesz_t>(qty);
        if(qty > 1) {
            offlist.reserve(qty);
        }
        // list itself
        for(size_t j = 0; j<qty; j++) {
            pagesz_t pageoff;
            in.read(reinterpret_cast<char*>(&pageoff), sizeof(pagesz_t));
            offlist.push_back(native_endian<pagesz_t>(pageoff));
        }

        page[inword] = offlist;
    }
}
        
filesz_t decompapp::writepage(std::ostream &out, Page &page, filesz_t nWritten, filesz_t fileSize) const {

    size_t nToWrite = std::min(page.size*sizeof(word_t), fileSize-nWritten);
    
    out.write(reinterpret_cast<const char*>(page.buffer), nToWrite);

    return nToWrite;
}
