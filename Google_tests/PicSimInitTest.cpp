#include "gtest/gtest.h"
#include "2_Application_Code/picSim.h"

class PicSimInitFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
        picData1->releaseInstance();
        ram1->releaseInstance();
    }
    picData *picData1 = picData::getPicDataObject();
    ram *ram1 = ram::getRamObject();
};

TEST_F(PicSimInitFixture, InitTrue){
    // Arrange
    picSim picSim1;

    // Act
    picSim1.init(true);

    // Assert
    EXPECT_EQ(picData1->getCycle(), 0);
    EXPECT_EQ(picData1->getProgramCounter(), 0);
    EXPECT_EQ(picData1->getWreg(), 0);
    EXPECT_EQ(picData1->getRuntime(), 0);
    EXPECT_EQ(picData1->getMultiplier(), 1);

    EXPECT_EQ(ram1->getRam(3), 24);
    EXPECT_EQ(ram1->getRam(131), 24);

    EXPECT_EQ(ram1->getRam(10), 0);
    EXPECT_EQ(ram1->getRam(11), 0);
    EXPECT_EQ(ram1->getRam(129), 255);
    EXPECT_EQ(ram1->getRam(133), 255);
    EXPECT_EQ(ram1->getRam(134), 255);
}

TEST_F(PicSimInitFixture, InitFalse){
    // Arrange
    picSim picSim1;

    // Act
    picSim1.init(false);

    // Assert
    EXPECT_EQ(picData1->getCycle(), 0);
    EXPECT_EQ(picData1->getProgramCounter(), 0);
    EXPECT_EQ(picData1->getWreg(), 0);
    EXPECT_EQ(picData1->getRuntime(), 0);
    EXPECT_EQ(picData1->getMultiplier(), 1);

    EXPECT_EQ(ram1->getRam(3), 0);
    EXPECT_EQ(ram1->getRam(131), 0);

    EXPECT_EQ(ram1->getRam(10), 0);
    EXPECT_EQ(ram1->getRam(11), 0);
    EXPECT_EQ(ram1->getRam(129), 255);
    EXPECT_EQ(ram1->getRam(133), 255);
    EXPECT_EQ(ram1->getRam(134), 255);
}