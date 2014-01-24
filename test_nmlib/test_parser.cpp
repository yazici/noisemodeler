#include <nmlib/parser.hpp>

#include <gtest/gtest.h>

TEST(ParserTest, Constructor) {
    nm::Parser* parser = new nm::Parser();
    delete parser;
    SUCCEED();
}


TEST(ParserTest, GracefulFailure){
    nm::Parser parser;
    auto modules = parser.parse("Malformed");
    EXPECT_FALSE(modules);
}

TEST(ParserTest, BlankDocument){
    nm::Parser parser;
    auto modules = parser.parse("{\"moduleTypes\":[]}");
    if(!modules){
        FAIL();
    }
    EXPECT_EQ((*modules).size(), 0);
}
