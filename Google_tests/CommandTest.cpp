#include "gtest/gtest.h"
#include "2_Application_Code/decode.h"
#include "2_Application_Code/picSim.h"


class CommandTestFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
       picData1->releaseInstance();
       ram1->releaseInstance();
    }
    picData *picData1 = picData::getPicDataObject();
    picSim picSim1;
    ram *ram1 = ram::getRamObject();
};

TEST_F(CommandTestFixture, nop) {

    // Arrange
    decode decodeCommand("00000000000000");

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(picData1->getWreg(), 0);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

TEST_F(CommandTestFixture, incf) {

    // Arrange
    decode decodeCommand("00101000000110");
    ram1->setRam(6, 2, 0);

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(picData1->getWreg(), 3);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

TEST_F(CommandTestFixture, movwf) {

    // Arrange
    decode decodeCommand("00000010001000");
    picData1->setWreg(16);

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(ram1->getRam(8), 16);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

TEST_F(CommandTestFixture, decf) {

    // Arrange
    decode decodeCommand("00001100000100");
    ram1->setRam(4, 4, 0);

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(picData1->getWreg(), 3);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

TEST_F(CommandTestFixture, movlw) {

    // Arrange
    decode decodeCommand("11000000001101");
    ram1->setRam(4, 4, 0);

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(picData1->getWreg(), 13);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

TEST_F(CommandTestFixture, xorlw) {

    // Arrange
    decode decodeCommand("11101000001110");
    picData1->setWreg(42);

    // Act
    picSim1.executecmd(decodeCommand.decodeCommand());

    // Assert
    EXPECT_EQ(picData1->getCycle(), 1);
    EXPECT_EQ(picData1->getProgramCounter(), 1);
    EXPECT_EQ(picData1->getWreg(), 36);
    EXPECT_EQ(picData1->getRuntime(), 1);
    EXPECT_EQ(picData1->getMultiplier(), 1);
}

