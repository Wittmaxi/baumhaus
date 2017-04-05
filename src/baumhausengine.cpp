#include "baumhausengine.h"

#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CBaumhausengine::CBaumhausengine()
{
    position = new CPos;
    pipe = new CPipe;
    //ctor
}

CBaumhausengine::~CBaumhausengine()
{
    //dtor
}

std::string CBaumhausengine::readPipe() {
    return pipe->getLastMessage();
}

void CBaumhausengine::analyzePos(CPos position) {

}

void CBaumhausengine::updateSquares() {

}
