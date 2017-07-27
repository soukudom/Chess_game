#include "CGame.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

    CGame::CGame()
    {
        m_player = 'W';
    }

    CGame::~CGame()
    {

    }

    void CGame::ChessGame()
    {
    int c;
    char name [31], file[50];
    bool mov;
        while(!IsGameOver())
        {
        m_game.Print(m_player);
        cout << "** Select option:\n   1) Make move\n   2) Save game\n   3) Load game\n   4) End game\n   5) Instruction" << endl;
            cin >> c;
            if(c > 5 || c < 1 || !cin.good())
            {
                cout << "!! Bad option" << endl;
                m_game.Clear();

            }
        switch(c)
        {
            case 1:
                if( m_game.Move(m_player) )
                {
                    m_game.Change(m_player);
                    Next();
                    if(m_game.IsCheck(m_player))
                    {
                        mov = m_game.PossibleMove(m_player);
                        if(mov)
                            cout << "** Check" << endl;
                    }
                 }
                break;
            case 2:
                strcpy(file,"examples/");
                cout << "** Type file name: ";
                if(cin.peek() == '\n')
                    cin.get(); //clean \n in buffer
                cin.getline(name,31,'\n');

                if(!cin.good())
                    m_game.Clear();

                if( m_game.Save(m_player,strcat(file,name)) )
                    cout << "** Game saved" << endl;
                else
                    cout << "** Game not saved" << endl;
                break;
            case 3:
                    strcpy(file,"examples/");
                    cout << "** Type file name: ";
                    if(cin.peek() == '\n')
                        cin.get(); //clean \n in buffer
                    cin.getline(name,31,'\n');

                    if( m_game.Load(&m_player, strcat(file,name)) )
                    {
                        cout << "** Game loaded" << endl;
                    }
                    else
                    {
                        cout << "** Loading problem. Game not loaded." << endl;
                    }
                break;
            case 4:
                cout << "End game" << endl;
                m_game.Release();
                exit(0);
            case 5:
                cout << "*****  Chess game Instruction  *****" << endl;
                cout << "MOVING" << endl;
                cout << "If you want to move with piece press number 1 in default menu and insert at first source position and then destination position. ";
                cout << "Rows are labeled by number 1-8 and columns are labeled by letter A-H. So the valid move for white pawn could be A2 A4. ";
                cout << "It not depend on white characters but it is very important write big letters. For example move for white pawn a2 a4 are not allowed and you must insert A2 A4.";
                cout << "When insert move which is against standard chess rules (choose piece which is not in turn, insert not allowed move, destination position is not on game board) ";
                cout << "an error message is displayed and you are returned back to main menu, where you can retype the move."<< endl << endl;
                cout << "SAVING" << endl;
                cout << "If you want to save you game press number 2 in default menu and type name of file. ";
                cout << "The file name length is restrict on 30 characters. If you type longer filename it will be restrict. ";
                cout << "If the game can not be save you get the message and you are returned back to the main menu." << endl << endl;
                cout << "LOADING" << endl;
                cout << "If you want to load your game press number 3 in default menu and type name of file. ";
                cout << "The file name length is restrict on 30 characters. If you type longer filename it will be restrict. ";
                cout << "If the file do not exists you get the message and you are returned back to the main menu." <<endl << endl;
                cout << "Press return to continue...";
                if(cin.peek() == '\n')
                    cin.get();
                m_game.Clear();

        }

        }

    }

    void CGame::Next()
    {
        if(m_player == 'W')
        {
            m_player = 'B';
        }
        else
        {
            m_player = 'W';
        }
        //change set flag for en passant move
        m_game.ControlFlag(m_player);
    }

    bool CGame::IsGameOver()
    {
        bool mov = m_game.PossibleMove(m_player);

        if(!mov)
        {
            if(m_game.IsCheck(m_player))
            {
                string winner = (m_player == 'W') ? "Black" : "White";
                cout << "Check mate. " << winner << " wins" << endl;
                return true;
            }
            else
            {
                cout << "Stale mate"  << endl;
                return true;
            }
        }

        else
        {
            return false;
        }

    }
