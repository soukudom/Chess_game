/** \file CPawn.h
 *  Header for CPawn class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///Pawn
class CPawn : public CPiece
{
    public:
        ///Constructor
        /** Constructor which create pawn for specific player
        * \param color Color of player */
                 CPawn(char color);
        virtual ~CPawn();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board [8][8]) ;
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int);
        ///Control en passant move
        /** This method control if en passant move is possible for pawn
        \return true if en passant move is possible else return false */
        bool     EnPassant(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8]);
        ///Control attack move
        /**This method control if pawn can do attack move
        * \return true if pawn can do attack move else return false */
        bool     Attack(int srcRow, int srcCol, int dstRow, int dstCol);
        ///Control normal move
        /**This method control if normal move is possible for pawn
        * \return true if normal move is possible else return false */
        bool     Classic(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8]);
};
