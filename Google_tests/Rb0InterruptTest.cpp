#include "gtest/gtest.h"
#include "2_Application_Code/picSim.h"

class Rb0InterruptFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
        picSim1 = new picSim();
    }
    virtual void TearDown() {
        picData1->releaseInstance();
        ram1->releaseInstance();
        customStack1->releaseInstance();
        delete picSim1;
    }
    picData *picData1 = picData::getPicDataObject();
    ram *ram1 = ram::getRamObject();
    customStack *customStack1 = customStack::getcustomStackObject();
    picSim *picSim1;
};

TEST_F(Rb0InterruptFixture, IntEdgTrue){
    // Arrange
    ram1->setRam(11,128+16);
    ram1->setRam(129,64);

    // Act
    picSim1->rb0interrupt();

    // Assert
    EXPECT_EQ(picSim1->getIntEdg(),1);
}

TEST_F(Rb0InterruptFixture, IntEdgFalse){
    // Arrange
    ram1->setRam(11,0);
    ram1->setRam(129,0);

    // Act
    picSim1->rb0interrupt();

    // Assert
    EXPECT_EQ(picSim1->getIntEdg(),0);
}

TEST_F(Rb0InterruptFixture, InterruptEdge0){
    // Arrange
    ram1->setRam(11,128+16);
    ram1->setRam(129,0);
    picSim1->setEdge(false);

    // Act
    picSim1->rb0interrupt();

    // Assert
    EXPECT_EQ(picSim1->getEdge(),0);
    EXPECT_EQ(ram1->getRam(11),18);
    EXPECT_EQ(customStack1->top(),0);
    EXPECT_EQ(picData1->getProgramCounter(),4);
}

TEST_F(Rb0InterruptFixture, InterruptEdge1){
    // Arrange
    ram1->setRam(11,128+16);
    ram1->setRam(129,64);
    picSim1->setEdge(true);

    // Act
    picSim1->rb0interrupt();

    // Assert
    EXPECT_EQ(picSim1->getEdge(),1);
    EXPECT_EQ(ram1->getRam(11),18);
    EXPECT_EQ(customStack1->top(),0);
    EXPECT_EQ(picData1->getProgramCounter(),4);
}
