#include "gtest/gtest.h"
#include "0_Abstraction_Code/customStack.h"

class StackFixture : public ::testing::Test{
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
        customStack1->releaseInstance();
    }
    customStack *customStack1 = customStack::getcustomStackObject();
};

TEST_F(StackFixture, PushTest){
    // Arrange
    int i = 1;

    // Act
    customStack1->push(i);

    // Assert
    EXPECT_EQ(customStack1->top(),1);
}

TEST_F(StackFixture, PopTest){
    // Arrange
    for(int i = 1; i < 4; i++){
        customStack1->push(i);
    }

    // Act
    customStack1->pop();

    // Assert
    EXPECT_EQ(customStack1->top(),2);
}


TEST_F(StackFixture, GetStackTest){
    // Arrange
    for(int i = 1; i < 5; i++){
        customStack1->push(i);
    }

    // Act
    stackarray j = customStack1->getstack(2);

    // Assert
    EXPECT_EQ(j,3);
}

TEST_F(StackFixture, ClearStackTest){
    // Arrange
    for(int i = 1; i < 5; i++){
        customStack1->push(i);
    }

    // Act
    customStack1->clearStack();

    // Assert
    EXPECT_EQ(customStack1->top(),0);
}




