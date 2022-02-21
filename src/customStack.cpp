#include "../header/customStack.h"

customStack *customStack::customStackObject = nullptr;
customStack *customStack::getcustomStackObject() {
    if (customStackObject == nullptr) {
        customStackObject = new customStack();
    }
    return customStackObject;
}
void customStack::push(int value) {
    if (content == 0) {
        index = 0;
    }
    if (index > 7) {
        index = index - 8;
    }
    stack[index] = value;
    index++;
    content++;
}
stackarray customStack::top() {
    if (index > 8) {
        index = index - 8;
    }
    if (index < 1) {
        index = index + 8;
    }
    return stack[index - 1];
}
void customStack::pop() {
    if (index < 1) {
        index = index + 8;
    }
    stack[index - 1] = 0;
    index--;
    if (content != 0) {
        content--;
    }
}
stackarray customStack::getstack(int pos) {
    return stack[pos];
}
void customStack::clearStack() {
    stack.fill(0);
    index = 0;
}
std::array<stackarray, 8> customStack::getStack() {
    return stack;
}
void customStack::setStack(std::array<stackarray, 8> lstack) {
    stack = lstack;
}
