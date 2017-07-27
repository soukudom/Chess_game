/** \file CBishop.h
 *  Header for CBishop class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CPiece.h"

///Bishop
class CBishop : public CPiece
{
    public:
        ///Constructor
        /** Create bishop for specific player
        * \param color Color of player */
                 CBishop(char color);
        virtual ~CBishop();
        bool     IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]);
        char     GetPiece() const;
        char     GetColor() const;
        int      GetFlag()  const;
        void     SetFlag(int flag);
};
