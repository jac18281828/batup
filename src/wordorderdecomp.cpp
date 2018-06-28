#include <algorithm>
#include "wordorderdecomp.h"

using namespace batup;

void wordorderdecomp::decompress(const IndexedPage &indexedPage, Page &page) {

    page.size = 0UL;
    
    for(auto wordit = indexedPage.begin();
        wordit != indexedPage.end();
        ++wordit) {

        const word_t outword = wordit->first;
        const std::vector<pagesz_t> &offlist = wordit->second;

        for(auto offit = offlist.begin();
            offit != offlist.end();
            ++offit) {
            pagesz_t offset = *offit;
            
            page.buffer[offset] = outword;

            if(offset+1u > page.size) {
                page.size = offset+1u;
            }
        }
    }
}


