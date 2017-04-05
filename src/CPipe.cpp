#include "CPipe.h"

#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPipe::CPipe()
{
    messageStack.clear();
    //ctor
}

CPipe::~CPipe()
{
    //dtor
}

std::string CPipe::getLastMessage() {
    return messageStack[messageStack.size()]; //returns the last message logged
}
