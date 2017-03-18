#ifndef MOVE_H
#define MOVE_H


class chessMove
{
    public:
		chessMove(int fromRow = 0, int fromCol = 0, int toRow = 0, int toCol = 0);
        unsigned int From[2];
        unsigned int To[2];
};

#endif // MOVE_H
