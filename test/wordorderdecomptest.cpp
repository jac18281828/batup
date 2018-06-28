#include "gtest/gtest.h"

#include "page.h"
#include "wordorderdecomp.h"

using namespace batup;

TEST(SizeCheck, WordOrderDeomp) {
    IndexedPage indPage;
    Page page;

    indPage[44] = {0, 2, 4, 6, 75};

    wordorderdecomp decomp;

    decomp.decompress(indPage, page);

    ASSERT_EQ(page.size, 76u);
}


TEST(SimpleDict, WordOrderDeomp) {
    IndexedPage indPage;
    Page page;

    indPage[0] = {0, 2, 4, 6, 8};
    indPage[1] = {1, 3, 5, 7, 9};

    wordorderdecomp decomp;

    decomp.decompress(indPage, page);

    ASSERT_EQ(page.size, 10u);

    for(size_t i = 0; i<10; i++) {
        ASSERT_EQ(page.buffer[i], i%2);
    }
}

TEST(FullSequence, WordOrderDecomp) {
    IndexedPage indPage;
    Page page;

    const size_t TEST_LEN = PAGE_WORDS;

    for(size_t i=0; i<4; i++) {
        indPage[i] = { };
        for(size_t j=i; j<TEST_LEN; j+=4) {
            indPage[i].push_back(j);
        }
    }
    
    wordorderdecomp decomp;

    decomp.decompress(indPage, page);
    
    ASSERT_EQ(page.size, TEST_LEN);

    for(size_t i=0; i<TEST_LEN; i++) {
        ASSERT_EQ(page.buffer[i], i % 4u);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
