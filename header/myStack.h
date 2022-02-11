#ifndef PICSIM2_0_MYSTACK_H
#define PICSIM2_0_MYSTACK_H


#include <array>
#include <bitset>

class myStack {
private:
    typedef std::bitset<13> stackarray;
    std::array<stackarray ,8>stack = { 0 };
    int index = 0;
    int content = 0;

public:
    void push(int value);
    stackarray top();
    void pop();
    stackarray getstack(int pos);
    void clearStack();
};


#endif //PICSIM2_0_MYSTACK_H
