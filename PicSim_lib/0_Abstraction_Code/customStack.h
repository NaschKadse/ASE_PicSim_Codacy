#ifndef ASE_PICSIM_CUSTOMSTACK_H
#define ASE_PICSIM_CUSTOMSTACK_H

#include <array>
#include <bitset>

typedef std::bitset<13> stackarray;

class customStack {
public:
    static customStack *getcustomStackObject();
    void push(int value);
    stackarray top();
    void pop();
    stackarray getstack(int pos);
    void clearStack();
    std::array<stackarray, 8> getStack();
    void setStack(std::array<stackarray, 8> lstack);
private:
    customStack() {};
    ~customStack() {};
    static customStack *customStackObject;
    std::array<stackarray, 8> stack = {0};
    int index = 0;
    int content = 0;
};

#endif //ASE_PICSIM_CUSTOMSTACK_H
