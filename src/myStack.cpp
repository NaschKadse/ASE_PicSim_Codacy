#include "../header/myStack.h"


typedef std::bitset<13> stackarray;
void myStack::push(int value){
    if(content == 0){
        index = 0;
    }
    if(index > 7){
        index = index - 8;
    }
    stack[index] = value;
    index++;
    content++;
}

stackarray myStack::top(){
    if(index > 8){
        index = index - 8;
    }
    if(index < 1){
        index = index + 8;
    }
    return stack[index-1];
}

void myStack::pop(){

    if(index < 1){
        index = index + 8;
    }
    stack[index-1] = 0;
    index--;
    if(content != 0){
        content--;
    }
}


stackarray myStack::getstack(int pos){
    return stack[pos];
}

void myStack::clearStack(){
    stack.fill(0);
    index = 0;
}