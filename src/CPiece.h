#ifndef CPIECE_H
#define CPIECE_H

#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


class CPiece: public PPawn; PRook; PKnight; PBishop; PQueen; PKing;
{
    public:
        CPiece();
        virtual ~CPiece();

    protected:

    private:
        std::string type; //contains the type of piece in a string (provisory)
};

#endif // CPIECE_H
