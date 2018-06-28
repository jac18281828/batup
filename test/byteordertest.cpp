#include "gtest/gtest.h"

#include "byteorder.h"

TEST(IsBigEndian, ByteOrder) {
    if(__BYTE_ORDER == __ORDER_BIG_ENDIAN__) {
        ASSERT_TRUE(batup::is_big_endian());
    } else {
        ASSERT_FALSE(batup::is_big_endian());        
    }
}

TEST(ToBigEndian, ByteOrder) {

    const unsigned short testValue = (unsigned short)batup::is_big_endian() ? 0xBBAAU : 0xAABBU;
    
    ASSERT_EQ(batup::big_endian<unsigned short>(testValue) >> 8, 0xBB);    
}


TEST(ToBigEndianLong, ByteOrder) {

    const unsigned long testValue =  0x1122334455667788UL;

    if(batup::is_big_endian()) {
        ASSERT_EQ(batup::big_endian<unsigned long>(testValue), testValue);
    } else {
        ASSERT_EQ(batup::big_endian<unsigned long>(testValue), 0x8877665544332211UL);        
    }
}


TEST(ToNativeEndian, ByteOrder) {


    const unsigned short testValue = 0xAABBU;

    if(batup::is_big_endian()) {
        ASSERT_EQ(batup::native_endian<unsigned short>(testValue), testValue);
    } else {
        ASSERT_EQ(batup::native_endian<unsigned short>(testValue), 0xBBAAU);
    }
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
