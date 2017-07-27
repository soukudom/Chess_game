/** \file CPiece.h
 *  Header for CPiece abstract class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

/** \mainpage
*  This project implements a chess game in bash terminal for two players.
*   You can load and save the game.
*
*   For more detailed documentation see the coments in each file.
*
*   \author Dominik Soukup <soukudom@fit.cvut.cz>*/

#ifndef CP
#define CP

///Piece
/** Abstract class, whitch representing basic skills for each piece. */
class CPiece
{
    public:
        ///Destructor
        virtual ~CPiece() {}
        ///Checks if move is valid
        /**This virtual method check if move of piece on board is valid.
        * \param srcRow Number of row where the piece is
        * \param srcCol Number of column where the piece is
        * \param dstRow Number of row to where the piece may move
        * \param dstCol Number of column to where the piece may move
        * \param *board[8][8]  Chess board
        * \return true if move is valid or false if not*/
        virtual bool IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8]) = 0;
        ///Get piece name
        /** \return Name of piece */
        virtual char GetPiece() const = 0;
        ///Get piece color
        /** \return Color of piece */
        virtual char GetColor() const = 0;
        ///Get piece flag
        /**The flag representig the state in which the piece actually is.
        * On flag state is depend the move.
        * \return Number of flag state */
        virtual int GetFlag()  const = 0;
        ///Set piece flag
        /**This method allow set flag state from other classes
        * \param Number of changing state */
        virtual void SetFlag(int) = 0;

    protected:
        /// Flag state
        /** The flag representig the state in which the piece actually is.
        * On flag state is depend the move. */
        int m_flag;
        /// Color of piece
        char m_color;
        /// Name of piece
        char m_type;

};

#endif
