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

void CBaumhausengine::setColor(bool colorI) { //the playing-color
    color = colorI;
}

bool CBaumhausengine::getColor() {
    return color;
}

void CBaumhausengine::startRoutine() {
  while (!(gotPipeInput)) { //just simply spools to wait for a signal

  }
}
