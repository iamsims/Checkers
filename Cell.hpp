#pragma once

enum Color{
	WHITE,
	BLACK
};

enum TYPE{
			EMPTY,
			WHITE_PAWN,
			YELLOW_PAWN,
			WHITE_KING,
			YELLOW_KING
};

class Cell{
	public:
		Cell();
		TYPE getTYPE() const;
		void setTYPE(TYPE type);

	private:
		TYPE _type;
};
