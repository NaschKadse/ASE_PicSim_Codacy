#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "2_Application_Code/utility.h"

class ToBinaryMock{
public:
    MOCK_METHOD(std::string, toBinary, ());
};

TEST(ToBinaryMockTest, Mock101010){
    // Arrange
    ToBinaryMock toBinaryMock;
    std::string actual = "101010";

    EXPECT_CALL(toBinaryMock, toBinary())
    .Times(1)
    .WillRepeatedly(::testing::Return("101010"));

    // Act
    std::string expect = toBinaryMock.toBinary();

    // Assert
    EXPECT_EQ(expect, actual);
}
