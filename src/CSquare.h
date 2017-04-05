#ifndef CSQUARE_H
#define CSQUARE_H


class CSquare
{
    public:
        CSquare();
        virtual ~CSquare();

    protected:
        int protection; //how much the square is protected: example: -1 means, black has protected the square one more time as white. When a piece is on the square it doesn't count as protected
        bool hasPiece; //if a piece is placed on the square.


    private:
};

#endif // CSQUARE_H
