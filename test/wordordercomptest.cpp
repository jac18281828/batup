#include "gtest/gtest.h"

#include "wordordercomp.h"

using namespace batup;

TEST(SimpleThreeElement, WordOrderComp) {
    IndexedPage outputPage;
    Page page;
    
    page.buffer[0] = 1;
    page.buffer[1] = 2;
    page.buffer[2] = 3;
    page.buffer[3] = 4;
    page.size = 3;

    wordordercomp comp;

    comp.compress(page, outputPage);

    ASSERT_EQ(outputPage.size(), 3u);
    for(int i=0; i<3; i++) {
        ASSERT_EQ(outputPage[i+1].size(), 1u);
        ASSERT_EQ(outputPage[i+1][0], (pagesz_t)i);
    }
}

TEST(FullUnique, WordOrderComp) {
    IndexedPage outputPage;
    Page page;

    for(unsigned i=0; i<PAGE_WORDS; i++) {
        page.buffer[i] = i+1;
    }

    page.size = PAGE_WORDS;

    wordordercomp comp;

    comp.compress(page, outputPage);

    ASSERT_EQ(outputPage.size(), PAGE_WORDS);
    for(size_t i=0; i<PAGE_WORDS; i++) {
        ASSERT_EQ(outputPage[i+1].size(), 1u);
        ASSERT_EQ(outputPage[i+1][0], (pagesz_t)i);
    }
}

TEST(ManyToFew, WordOrderComp) {
    IndexedPage outputPage;
    Page page;

    const size_t TEST_LEN = PAGE_WORDS;
    
    for(size_t i=0; i<TEST_LEN; i++) {
        page.buffer[i] = i % 4u;
    }

    page.size = TEST_LEN;

    wordordercomp comp;

    comp.compress(page, outputPage);

    ASSERT_EQ(outputPage.size(), 4u);
    for(size_t i=0; i<4; i++) {
        ASSERT_EQ(outputPage[i].size(), TEST_LEN/4u);
    }

    // 0: 0, 4, 8, 12 ...
    // 1: 1, 5, 9, 13 ...
    // 2: 2, 6, 10, 14 ...
    // 3: 3, 7, 11, 15 ...

    for(size_t i=0; i<4; i++) {
        for(size_t j=i; j<TEST_LEN; j+=4) {
            ASSERT_EQ(outputPage[i][j/4], (pagesz_t)j);
        }
    }
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
