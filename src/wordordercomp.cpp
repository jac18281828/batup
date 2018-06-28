#include <iostream>
#include "wordordercomp.h"

using namespace batup;

void wordordercomp::compress(const Page &page, IndexedPage &indexedPage) {
    
    for(size_t i = 0; i<page.size; i++) {

        const word_t value = page.buffer[i];
        
        auto rc = indexedPage.find(value);

        if(rc == indexedPage.end()) {
            std::vector<pagesz_t> initialVec = { static_cast<pagesz_t>(i) };
            
            indexedPage.insert({value, initialVec});
        } else {
            rc->second.push_back(i);
        }
    }

}

