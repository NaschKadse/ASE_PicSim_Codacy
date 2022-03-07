#include "gtest/gtest.h"
#include "0_Abstraction_Code/ram.h"

class RamTestFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
        ram1->releaseInstance();
    }
    ram *ram1 = ram::getRamObject();
};

TEST_F(RamTestFixture, SetTest){
    // Arrange
    int pos = 5;
    int content = 3;

    // Act
    ram1->setRam(pos, content);

    // Assert
    EXPECT_EQ(ram1->getRamGui(5), 3);
}

TEST_F(RamTestFixture, SetTestMirroring){
    // Arrange
    int pos2 = 2;
    int pos3 = 3;
    int pos4 = 4;
    int pos10 = 10;
    int pos11 = 11;
    int content = 3;

    // Act
    ram1->setRam(pos2, content);
    ram1->setRam(pos3, content);
    ram1->setRam(pos4, content);
    ram1->setRam(pos10, content);
    ram1->setRam(pos11, content);

    // Assert
    EXPECT_EQ(ram1->getRamGui(2), ram1->getRamGui(130));
    EXPECT_EQ(ram1->getRamGui(3), ram1->getRamGui(131));
    EXPECT_EQ(ram1->getRamGui(4), ram1->getRamGui(132));
    EXPECT_EQ(ram1->getRamGui(10), ram1->getRamGui(138));
    EXPECT_EQ(ram1->getRamGui(11), ram1->getRamGui(139));
}

TEST_F(RamTestFixture, RP0FalseTest){

    // Arrange
    int pos = 9;
    int content = 42;
    ram1->setRam(3, 0);

    // Act
    ram1->setRam(pos, content);


    // Assert
    EXPECT_EQ(ram1->getRamGui(9), 42);
    EXPECT_FALSE(ram1->getRamGui(137) == 42);

}

TEST_F(RamTestFixture, RP0TrueTest){

    // Arrange
    int pos = 9;
    int content = 42;
    ram1->setRam(3, 255);

    // Act
    ram1->setRam(pos, content);


    // Assert
    EXPECT_EQ(ram1->getRamGui(137), 42);
    EXPECT_FALSE(ram1->getRamGui(9) == 42);

}
