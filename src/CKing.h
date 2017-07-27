/** \file CKing.h
 *  Header for CKing class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///King
class CKing : public CPiece
{
    public:
        ///Constructor
        /** Constructor which create king for specific player
        * \param color Color of player */
                 CKing(char color);
        virtual ~CKing();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]) ;
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int);
        ///Checks if squar is safety
        /**Safety mean that no piece can no attack to king
        *\param *board[8][8] Chess board
        *\param color Color of player
        *\param sRow Number of row where the king is
        *\param sCol Number of column where the king is
        *\return true if position is safety else return false */
        bool     IsSafety(CPiece * board [8][8], char color, int sRow, int sCol) const;
        ///Control possibility of castling move
        /** \return true if move is possible else return false */
        bool     CastlingMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8], char color);

};
