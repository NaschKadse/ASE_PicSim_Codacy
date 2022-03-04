#include "gtest/gtest.h"
#include "2_Application_Code/picSim.h"

TEST(CratePCLTestSuit, CorrectString){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = picSim::createPCL("0101010101010");

    // Assert
    EXPECT_EQ(a,b);
}

TEST(CratePCLTestSuit, IncorrectString){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = picSim::createPCL("0101010101000");

    // Assert
    EXPECT_TRUE(a != b);
}

TEST(CratePCLTestSuit, IncorrectStringLengthToShort){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = picSim::createPCL("101010101010");

    // Assert
    EXPECT_TRUE(a != b);
}

TEST(CratePCLTestSuit, IncorrectStringLengthToLong){
    // Arrange
    BYTE a;
    BYTE b = 170;

    // Act
    a = picSim::createPCL("10101010101010");

    // Assert
    EXPECT_TRUE(a != b);
}
