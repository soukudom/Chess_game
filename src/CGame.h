/** \file CGame.h
 *  Header for CGame class.
 *  \author Dominik Soukup <soukudom@fit.cvut.cz> */

#include "CBoard.h"
#include "CPiece.h"
#include <string>

///Chess game
/** This class control the process of game */
class CGame
{
    public:
    ///Constructor
        /**Choose white player like starting player and preapare the game */
                CGame();
        ///Destructor
        virtual ~CGame();
        ///Change turn
        /**Change player who is in turn */
        void     Next();
        ///Check game over
        /** When the game is over print on standart output the result (check mate or stale mate)
        *\return true when no next turn is possbile else return false */
        bool     IsGameOver();
        ///Starts game
        /**Main method which control process of game*/
        void     ChessGame();


    private:
        ///Chess board
        CBoard  m_game;
        ///Color of player who is in turn
        char    m_player;
};
