#ifndef CPIECE_H
#define CPIECE_H

class CPiece {
	public:
			void setCoordinates (int cordXI, int cordYI){
					cordX = cordXI;
					cordY = cordYI;
			}
			bool getColor() {
				return (color);
			}
	protected:
			int cordX; //the coordinates of the piece.
			int cordY;
			std::string nameContained();
			bool color; //the figurine color. True means white. LOL.
};

#endif // CPIECE_H
