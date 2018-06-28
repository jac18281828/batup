#include <exception>

#include "gtest/gtest.h"

#include "properties.h"

using namespace batup;

TEST(BatupDefaultCompress, ParseCommandLine) {

    const char* argv[] = {"batup"};
  
    properties testprops = parse_command_line( 1, argv );

    ASSERT_FALSE(testprops.is_decompress());
}


TEST(BatdownDefaultCompress, ParseCommandLine) {

    const char* argv[] = {"batdown"};
    
    properties testprops = parse_command_line( 1, argv );

    ASSERT_TRUE(testprops.is_decompress());
}


TEST(MustThrowInvalidException, ParseCommandLine) {
    const char* argv[] = {"batup", "-notvalid"};

    ASSERT_THROW(parse_command_line(2, argv), std::exception);
}

TEST(DefaultStdout, ParseCommandLine) {
    const char* argv[] = {"batup"};

    properties testprops = parse_command_line(1, argv);

    ASSERT_TRUE(testprops.use_stdout());
}


TEST(WriteTostdout, ParseCommandLine) {
    const char* argv[] = {"batup", "-c"};

    properties testprops = parse_command_line(2, argv);

    ASSERT_TRUE(testprops.use_stdout());
}

TEST(BatDownWriteTostdout, ParseCommandLine) {
    const char* argv[] = {"batdown", "-c"};

    properties testprops = parse_command_line(2, argv);

    ASSERT_TRUE(testprops.use_stdout());
}

TEST(OutfileIsSet, ParseCommandLine) {
    const char* argv[] = {"batdown", "theoutfile", "-d"};

    properties testprops = parse_command_line(2, argv);

    ASSERT_EQ(testprops.getDatafile(), "theoutfile");
}


TEST(BatupDecompress, ParseCommandLine) {
    const char* argv[] = {"batup", "-c", "-d"};

    properties testprops = parse_command_line(3, argv);
    
    ASSERT_TRUE(testprops.is_decompress());
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
