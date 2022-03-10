#include "gtest/gtest.h"
#include "1_Domain_Code/command.h"

TEST(CratePCLTestSuit, CorrectString){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = command::createPCL("0101010101010");

    // Assert
    EXPECT_EQ(a,b);
}

TEST(CratePCLTestSuit, IncorrectString){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = command::createPCL("0101010101000");

    // Assert
    EXPECT_TRUE(a != b);
}

TEST(CratePCLTestSuit, IncorrectStringLengthToShort){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = command::createPCL("101010101010");

    // Assert
    EXPECT_TRUE(a != b);
}

TEST(CratePCLTestSuit, IncorrectStringLengthToLong){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = command::createPCL("10101010101010");

    // Assert
    EXPECT_TRUE(a != b);
}
