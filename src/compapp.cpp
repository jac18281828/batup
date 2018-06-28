#include <cstring>
#include <climits>

#include "compapp.h"
#include "wordordercomp.h"
#include "compressor.h"
#include "byteorder.h"

using namespace batup;

compapp::compapp(const properties &props, compressor *comp) : app(props), comp(comp) {
}

void compapp::process(std::istream &in, std::ostream &out) {

    filesz_t fileSize = 0L;

    // save space for header
    writeheader(out, 0L);
    
    while(!in.eof()) {
        Page inputPage;
        IndexedPage outputPage;
        fileSize += readpage(in, inputPage);

        comp->compress(inputPage, outputPage);
        
        writeidx(out, outputPage);

        if(!out) {
            error("Stopping");
            return;
        }
    }

    // overwrite header with correct values
    writeheader(out, fileSize);
}

size_t compapp::readpage(std::istream &in, Page &page) const {
    char* inputbuffer = reinterpret_cast<char*>(page.buffer);
    
    in.read(inputbuffer, PAGE_SIZE);

    size_t nRead;

    if(in) {
        nRead = PAGE_SIZE;
        page.size = PAGE_WORDS;
    } else {
        nRead = in.gcount();
        memset(inputbuffer + nRead, 0, PAGE_SIZE - nRead);
        page.size = nRead/sizeof(word_t) + 1;
        if ((nRead % sizeof(word_t)) > 0) {
            page.size += 1;
        }
    }
    return nRead;
}

void compapp::writeheader(std::ostream &out, filesz_t fileSize) const {

    magic_t magic = big_endian<magic_t>(MAGIC);
    filesz_t fileSz = big_endian<filesz_t>(fileSize);

    out.seekp(0L, std::ios_base::beg);
    out.write(reinterpret_cast<const char*>(&magic), sizeof(magic_t));
    out.write(reinterpret_cast<const char*>(&fileSz), sizeof(filesz_t));
}
        
void compapp::writeidx(std::ostream &out, IndexedPage &indPage) const {

    const pagesz_t pagewords = big_endian<pagesz_t>(indPage.size());
    out.write(reinterpret_cast<const char*>(&pagewords), sizeof(pagesz_t));
    
    for ( auto wordit = indPage.begin(); wordit != indPage.end(); ++wordit ) {
        const word_t outword = big_endian<word_t>(wordit->first);
        const std::vector<pagesz_t> &offlist = wordit->second;

        out.write(reinterpret_cast<const char*>(&outword), sizeof(word_t));

        const pagesz_t qty = big_endian<pagesz_t>(offlist.size());

        out.write(reinterpret_cast<const char*>(&qty), sizeof(pagesz_t));

        for(size_t i=0; i<offlist.size(); i++) {
            const pagesz_t pageoff = big_endian<pagesz_t>(offlist[i]);
            out.write(reinterpret_cast<const char*>(&pageoff), sizeof(pagesz_t));            
        }
    }
}
