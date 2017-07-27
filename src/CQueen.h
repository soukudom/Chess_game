/** \file CQueen.h
 *  Header for CQueen class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///Queen
class CQueen : public CPiece
{
    public:
        ///Constructor
        /** Constructor which create queen for specific player
        * \param color Color of player */
                 CQueen(char color);
        virtual ~CQueen();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]);
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int);
        ///Control normal move
        /**This method control if normal move is possible for queen
        * \return true if normal move is possible else return false */
        bool     Classic(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8]);

};
