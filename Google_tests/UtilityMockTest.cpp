#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "3_Plugins/LSTFileHandler.h"
#include "2_Application_Code/handler.h"

class UtilityMock : public utility {
public:
    virtual ~UtilityMock() {}

    MOCK_METHOD(void, setToBin, (int), (override));
    MOCK_METHOD(void, setDigits, (int), (override));
    MOCK_METHOD(std::string, toBinary, (), (override));
    MOCK_METHOD(void, setToFill, (std::string), (override));
    MOCK_METHOD(std::string, fillup, (), (override));
};

TEST(UtilityMockTest, readFileTPicSim1LST) {
    // Arrange
    UtilityMock utilityMock;
    picData *picData1 = picData::getPicDataObject();
    LSTFileHandler lstFileHandler;

    EXPECT_CALL(utilityMock, setToBin(::testing::_))
            .Times(::testing::Exactly(7));

    EXPECT_CALL(utilityMock, setDigits(14))
            .Times(::testing::Exactly(7));

    EXPECT_CALL(utilityMock, toBinary())
            .Times(::testing::Exactly(7))
            .WillRepeatedly(::testing::Return("Test1"));

    EXPECT_CALL(utilityMock, setToFill("Test1"))
            .Times(::testing::Exactly(7))
            .WillRepeatedly(::testing::Return());

    EXPECT_CALL(utilityMock, fillup())
            .Times(::testing::Exactly(7))
            .WillOnce(::testing::Return("Test2"))
            .WillOnce(::testing::Return("Test3"))
            .WillOnce(::testing::Return("Test4"))
            .WillOnce(::testing::Return("Test5"))
            .WillOnce(::testing::Return("Test6"))
            .WillOnce(::testing::Return("Test7"))
            .WillOnce(::testing::Return("Test8"));

    // Act
    lstFileHandler.readFile("../../LST/TPicSim1.LST", utilityMock);

    // Assert
    EXPECT_EQ(lstFileHandler.BinaryString, "Test1");
    EXPECT_EQ(picData1->getCommandArray(0), "Test2");
    EXPECT_EQ(picData1->getCommandArray(1), "Test3");
    EXPECT_EQ(picData1->getCommandArray(2), "Test4");
    EXPECT_EQ(picData1->getCommandArray(3), "Test5");
    EXPECT_EQ(picData1->getCommandArray(4), "Test6");
    EXPECT_EQ(picData1->getCommandArray(5), "Test7");
    EXPECT_EQ(picData1->getCommandArray(6), "Test8");
}