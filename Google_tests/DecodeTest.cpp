#include "gtest/gtest.h"
#include "2_Application_Code/decode.h"
#include "1_Domain_Code/command.h"


TEST(DecodeTestSuit, ClrfCorrectString){
    // Arrange
    decode decodeTest("00000110000001");
    command* cmdobject;

    // Act
    decode::decodedCmd decodedCmdStruct = decodeTest.decodeCommand();

    // Assert
    EXPECT_EQ(decodedCmdStruct.cmd, "normal");
    EXPECT_EQ(decodedCmdStruct.dBit, -1);
    EXPECT_EQ(decodedCmdStruct.filepos, 1);
    EXPECT_EQ(decodedCmdStruct.literal, -1);
    EXPECT_EQ(typeid(decodedCmdStruct.cmdobject), typeid(cmdobject));
}

TEST(DecodeTestSuit, BTFSSCorrectString){
    // Arrange
    decode decodeTest("01110010000100");
    command* cmdobject;

    // Act
    decode::decodedCmd decodedCmdStruct = decodeTest.decodeCommand();

    // Assert
    EXPECT_EQ(decodedCmdStruct.cmd, "normal");
    EXPECT_EQ(decodedCmdStruct.dBit, -1);
    EXPECT_EQ(decodedCmdStruct.filepos, 4);
    EXPECT_EQ(decodedCmdStruct.literal, 1);
    EXPECT_EQ(typeid(decodedCmdStruct.cmdobject), typeid(cmdobject));
}

TEST(DecodeTestSuit, ADDCorrectString){
    // Arrange
    decode decodeTest("11111000000010");
    command* cmdobject;

    // Act
    decode::decodedCmd decodedCmdStruct = decodeTest.decodeCommand();

    // Assert
    EXPECT_EQ(decodedCmdStruct.cmd, "normal");
    EXPECT_EQ(decodedCmdStruct.dBit, -1);
    EXPECT_EQ(decodedCmdStruct.filepos, -1);
    EXPECT_EQ(decodedCmdStruct.literal, 2);
    EXPECT_EQ(typeid(decodedCmdStruct.cmdobject), typeid(cmdobject));
}

TEST(DecodeTestSuit, InvalidString){
    // Arrange
    decode decodeTest("00000000000001");
    command* cmdobject;

    // Act
    decode::decodedCmd decodedCmdStruct = decodeTest.decodeCommand();

    // Assert
    EXPECT_EQ(decodedCmdStruct.cmd, "");
    EXPECT_EQ(decodedCmdStruct.dBit, -1);
    EXPECT_EQ(decodedCmdStruct.filepos, -1);
    EXPECT_EQ(decodedCmdStruct.literal, -1);
    EXPECT_EQ(typeid(decodedCmdStruct.cmdobject), typeid(cmdobject));
}