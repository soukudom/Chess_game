/** \file CKnight.h
 *  Header for CKnight class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///Knight
class CKnight : public CPiece
{
    public:
        ///Constructor
        /** Constructor which create knight for specific player
        * \param color Color of player */
                CKnight(char color);
        virtual ~CKnight();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]);
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int);

};
