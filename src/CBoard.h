/** \file CBoard.h
 *  Header for CBoard class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#ifndef BOARD
#define BOARD
#include "CPiece.h"

///Chess Board
/**This class reperesentig chess board. It allows control all pieces */
class CBoard
{
    public:
     ///Implicit constructor
        /**Create default game option */
                 CBoard();
        ///Destructor
        virtual ~CBoard();
        ///Print chess board
        /** Show every piece in game and also board indexes */
        void     Print(char) const;
        ///Check if game is in check
        /** \param color Color of player
        * \return true if the game is in check else false */
        bool     IsCheck(char);
        ///Save game
        /** \param color Color of player who is in turn
        * \param ofile Name of save file
        * \return true if saving was successful else return false */
        bool     Save(char, const char *) const;
        ///Load game
        /** \param color Color of player who is in turn
        *  \param name Name of load file
        *  \return true if loading was succesful else return false */
        bool     Load(char *, char *);
        ///Check if any piece can move
        /** When game is in check PossibleMove look if move of any piece can stop the check
        * \param color Color of player who is in turn
        * \return true if any piece can stop the check else return false */
        bool     PossibleMove(char);
        ///Check if pawn may change
        /** When pawn is located in last row in check board the player can choose bishop, knight, rook or queen instead of pawn
        * \param color Color of player who is in turn
        * \return true if any piece is located in last row of check board else return false */
        bool     Change(char);
        ///Piece movement
        /**This method reads source and destination positon of piece from standart input and make move if it is possible.
        *When the move is not possible or the position is bad you are returned to main menu and you can retype your move.
        *The format of position is along to rules of chess. First is letter of row (A-H) and then is number of column (1-8).
        *\param color Color of player who is in turn
        *\return true if move is right else return false*/
        bool     Move(char);
        ///Check flag of pawn for en passant move
        /**This method checks every pawn which make move two ranks forward from start position,
        *because after that the en passant move is possible but only for current turn. If the player
        *do not use this move he lost the right to do it.
        *\param color Color of player who is in turn*/
        void     ControlFlag(char) const;
        ///Release chess boad
        void     Release();
        ///Find king of specific color
        void     FindKing(int &, int &, char);
        ///Control if the move is right
        /**Control move parameters and if is anything wrong get help for it
        *\return true if move is right else return false */
        bool     MoveControl(char, int &, int &, int & , int &);
        ///Clear input stream buffer
        void     Clear();


    private:
    ///squares on chees board
        CPiece * m_board [8][8];


};

#endif
