/** \file CRook.h
 *  Header for CRook class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///Rook
class CRook : public CPiece
{
    public:
        ///Constructor
        /** Constructor which create rook for specific player
        * \param color Color of player */
                 CRook(char color);
        virtual ~CRook();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]);
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int);

};
