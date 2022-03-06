#include "gtest/gtest.h"
#include "3_Plugins/LSTFileHandler.h"
#include "2_Application_Code/handler.h"


class ReadFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
        picData1->releaseInstance();
    }
    LSTFileHandler lsthandler;
    picData *picData1 = picData::getPicDataObject();
};

TEST_F(ReadFixture, FirstCommandLine){
    // Arrange
    handler inputhandler(&lsthandler);

    // Act
    inputhandler.read("../../LST/TPicSim1.LST");

    // Assert
    EXPECT_EQ(picData1->getCommandArray(1), "11100100110000");
}

TEST_F(ReadFixture, SecondCommandLine){
    // Arrange
    handler inputhandler(&lsthandler);

    // Act
    inputhandler.read("../../LST/TPicSim1.LST");

    // Assert
    EXPECT_EQ(picData1->getCommandArray(2), "11100000001101");
}

TEST_F(ReadFixture, ThirdCommandLine){
    // Arrange
    handler inputhandler(&lsthandler);

    // Act
    inputhandler.read("../../LST/TPicSim1.LST");

    // Assert
    EXPECT_EQ(picData1->getCommandArray(3), "11110000111101");
}

TEST_F(ReadFixture, WrongPath){
    // Arrange
    handler inputhandler(&lsthandler);

    // Act
    inputhandler.read("../LST/TPicSim1.LST");

    // Assert
    EXPECT_EQ(picData1->getCommandArray(1),"");
}
