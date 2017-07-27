#include "CBoard.h"
#include "CRook.h"
#include "CBishop.h"
#include "CKing.h"
#include "CKnight.h"
#include "CQueen.h"
#include "CPawn.h"
#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

    CBoard::CBoard()
    {

        m_board[0][0] = new CRook('B');
        m_board[0][1] = new CKnight('B');
        m_board[0][2] = new CBishop('B');
        m_board[0][3] = new CQueen('B');
        m_board[0][4] = new CKing('B');
        m_board[0][5] = new CBishop('B');
        m_board[0][6] = new CKnight('B');
        m_board[0][7] = new CRook('B');

        for(int i = 0; i < 8; i++ )
        {
            m_board[1][i] = new CPawn('B');
        }

        m_board[7][0] = new CRook('W');
        m_board[7][1] = new CKnight('W');
        m_board[7][2] = new CBishop('W');
        m_board[7][3] = new CQueen('W');
        m_board[7][4] = new CKing('W');
        m_board[7][5] = new CBishop('W');
        m_board[7][6] = new CKnight('W');
        m_board[7][7] = new CRook('W');

        for(int i = 0; i < 8; i++ )
        {
            m_board[6][i] = new CPawn('W');
        }

        for(int i = 2; i < 6; i++ )
        {
            for(int j = 0; j < 8; j++)
            {
                m_board[i][j] = NULL;
            }
        }

    }

    CBoard::~CBoard()
    {
        Release();
    }

    void CBoard::Print(char player) const
    {
       int pom = 65;
        if(player == 'B')
        {
            cout << "\n**********************************" << endl;
            cout << "** Black player in turn" << endl << endl;
        }
        else
        {
            cout << "\n**********************************" << endl;
            cout << "** White player in turn" << endl << endl;
        }

        for(int i = 0; i < 8; i++ )
        {
         cout << 8-i << " # ";
            for(int j = 0; j < 8; j++)
            {
                if(m_board[i][j] == NULL)
                {
                    cout << "-- ";
                }
                else
                {
                    cout << m_board[i][j]->GetColor() << m_board[i][j]->GetPiece() << " ";
                }
            }
            cout << endl;
        }
        cout << "  # ";
        for(int i = 0; i < 8; i++)
        {
          cout << "## ";
        }
        cout << endl;
        cout << "    ";
        for(int i = 0; i < 8; i++)
        {
            cout << (char) pom << "  ";
            pom +=1;
        }
        cout << endl;
    }

    bool CBoard::PossibleMove(char color)
    {
        int oldFlag;
        //lookig at chessboard
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {   //find players piece, which is in turn
                if(m_board[row][col] != NULL && m_board[row][col]->GetColor() == color )
                {
                    for(int mRow = 0; mRow < 8; mRow++)
                    {
                        for(int mCol = 0; mCol < 8; mCol++)
                        {
                            //backup flag state
                            oldFlag = m_board[row][col]->GetFlag();
                            if(m_board[row][col]->IsValidMove(row,col,mRow,mCol,m_board))
                            {   //change position
                                CPiece * tmp = m_board[mRow][mCol];
                                m_board[mRow][mCol] = m_board[row][col];
                                m_board[row][col] = NULL;
                                bool movement = !IsCheck(color); //checking if movement can change check
                                //restore position
                                m_board[row][col] = m_board[mRow][mCol];
                                m_board[mRow][mCol] = tmp;
                                    m_board[row][col]->SetFlag(oldFlag);
                                if(movement)
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool CBoard::IsCheck(char color)
    {
        int kingRow, kingCol, oldFlag;
        //searching for king
        FindKing(kingRow,kingCol, color);

        //checking if someone can attack to king
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                if(m_board[row][col] != NULL)
                {
                    if(m_board[row][col]->GetColor() != color)
                    {
                        oldFlag = m_board[row][col]->GetFlag();
                        if(m_board[row][col]->IsValidMove(row,col,kingRow,kingCol,m_board))
                        {
                            return true;
                        }
                        m_board[row][col]->SetFlag(oldFlag);
                    }
                }
            }
        }

        return false;


    }

    bool CBoard::Save(char color, const char * oFile) const
    {

        char type, colorP;
        int flag;

        ofstream fout(oFile, ios_base::out | ios_base::binary);

        if(fout.is_open())
        {
            fout.write((char *) &color, sizeof color);
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(m_board[i][j] != NULL)
                    {   type = m_board[i][j]->GetPiece();
                        colorP = m_board[i][j]->GetColor();
                        flag = m_board[i][j]->GetFlag();
                        fout.write( (char *) &type , sizeof type);
                        fout.write( (char *) &colorP, sizeof colorP );
                        fout.write( (char *) &flag, sizeof flag );
                        fout.write( (char *) &i, sizeof i);
                        fout.write( (char *) &j, sizeof j);
                    }
                }
            }
        }
        else
        {
            fout.close();
            return false;
        }

        fout.close();
        return true;

    }

    bool CBoard::Load(char * color, char * name)
    {
        int row, col, flag;
        char type, colorP;
        if(strcmp(name,"examples/")==0)
        {
            return false;
        }
        ifstream fin(name, ios_base::in | ios_base::binary);
        if(fin.is_open())
        {   Release();
            fin.read((char *) color, sizeof *color);
            while (fin.read((char *) &type, sizeof type))
            {

                fin.read((char *) &colorP, sizeof colorP);
                fin.read((char *) &flag, sizeof flag);
                fin.read((char *) &row, sizeof row);
                fin.read((char *) &col, sizeof col);

                switch( type )
                {
                    case 'Q':
                        m_board[row][col] = new CQueen(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;
                    case 'R':
                        m_board[row][col] = new CRook(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;
                    case 'K':
                        m_board[row][col] = new CKing(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;
                    case 'B':
                        m_board[row][col] = new CBishop(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;
                    case 'N':
                        m_board[row][col] = new CKnight(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;
                    case 'P':
                        m_board[row][col] = new CPawn(colorP);
                        m_board[row][col]->SetFlag(flag);
                        break;

                }
            }
        }
        else
        {
            fin.close();
            return false;
        }
        fin.close();
        return true;

    }

    bool CBoard::Change(char color)
    {
    int col = -1;
        for(int i = 0;  i < 8; i++)
        {
            //check where the pawn is
            if( m_board[0][i] != NULL && m_board[0][i]->GetPiece() == 'P' )
            {
                col = 0;
            }
            else if( ( m_board[7][i] != NULL && m_board[7][i]->GetPiece() == 'P' ) )
            {
                col = 7;
            }

            if(col == 0 || col == 7)
            {
                int choice;
                while(true)
                {
                cout << "** Choose piece:\n   1) Queen\n   2) Row\n   3) Bishop\n   4) Knight" << endl;

                    cin >> choice;
                    if(choice > 4 || choice < 1 || !cin.good())
                    {
                        cout << "!! Bad option" << endl;
                        Clear();
                        continue;
                    }
                    break;
                }

                switch(choice)
                {
                    case 1:
                        delete m_board[col][i];
                        m_board[col][i] = new CQueen(color);
                        return true;;
                    case 2:
                        delete m_board[col][i];
                        m_board[col][i] = new CRook(color);
                        return true;;
                    case 3:
                        delete m_board[col][i];
                        m_board[col][i] = new CBishop(color);
                        return true;;
                    case 4:
                        delete m_board[col][i];
                        m_board[col][i] = new CKnight(color);
                        return true;
                }
            }
        }
        return false;

    }

    bool CBoard::Move(char color)
    {
     int sRow, sCol, dRow, dCol, psRow, pdRow;
     char psCol, dsCol;

        cout << "Insert move: ";
        cin >> psCol >> psRow >> dsCol >> pdRow;

        //control inserted move
        if( !isupper(psCol) || !isalpha(psCol) || !cin.good() ||
            !isupper(dsCol) || !isalpha(dsCol) )
        {

            cout << "!! Invalid parameters. See instruction for help." << endl;
            Clear();
            return false;

        }
        //converting position on board
        sCol = psCol - 65;
        dCol = dsCol - 65;

        if(psRow > 4)
        {
            sRow = 7 - ( 4 + (( psRow -1) % 4 ) );

        }
        else
        {
            sRow = 7 - ( psRow - 1 );
        }

        if(pdRow > 4)
        {
            dRow = 7 - ( 4 + (( pdRow -1) % 4 ) );
        }
        else
        {
            dRow = 7 - ( pdRow - 1 );
        }



        if(sRow < 0 || sRow > 7 || sCol < 0 || sCol > 7 ||
           dRow < 0 || dRow > 7 || dCol < 0 || dCol > 7)
        {
            cout << "!! Posision is out of range. See instruction for help" << endl;
            return false;
        }
        else
        {
            return MoveControl(color, sRow, sCol, dRow, dCol);
        }

    }

    void CBoard::ControlFlag(char color) const
    {

        //change set flag for en passant move
        for(int row = 0; row < 8; row ++)
        {
            for(int col = 0; col < 8; col ++)
            {
                if(m_board[row][col] != NULL && m_board[row][col]->GetPiece() == 'P' && m_board[row][col]->GetFlag() == 2 && color == m_board[row][col]->GetColor())
                {
                    m_board[row][col]->SetFlag(3);
                }
            }
        }

    }

    void CBoard::Release()
    {
        for(int i = 0; i < 8; i++ )
        {
            for(int j = 0; j < 8; j++)
            {
                if( m_board[i][j] != NULL )
                {
                    delete m_board[i][j];
                    m_board[i][j] = NULL;
                }
            }
        }

    }

    void CBoard::FindKing(int & kingRow, int & kingCol, char color)
    {
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                if(m_board[row][col] != NULL)
                {   //right color of king
                    if(m_board[row][col]->GetColor() == color)
                    {
                        if(m_board[row][col]->GetPiece()=='K')
                        {
                            kingRow = row;
                            kingCol = col;
                        }
                    }
                }
            }
        }

    }

    bool CBoard::MoveControl(char color,int & sRow, int & sCol, int & dRow, int & dCol)
    {
        int oldFlag;

            //check if was choosen a permit piece
            if( m_board[sRow][sCol] != NULL && m_board[sRow][sCol]->GetColor() == color )
            {   //backup flag state
                oldFlag = m_board[sRow][sCol]->GetFlag();
                if(m_board[sRow][sCol]->IsValidMove(sRow,sCol,dRow,dCol,m_board))
                {
                        CPiece * tmp = m_board[dRow][dCol];
                        m_board[dRow][dCol] = m_board[sRow][sCol];
                        m_board[sRow][sCol] = NULL;
                        if(m_board[dRow][dCol]->GetFlag() == 4)
                        {
                            if(sCol > dCol)
                            {
                                m_board[sRow][sCol-1] = m_board[sRow][0];
                                m_board[sRow][0] = NULL;
                            }
                            else
                            {
                                m_board[sRow][sCol+1] = m_board[sRow][7];
                                m_board[sRow][7] = NULL;
                            }
                        }
                    //if the move is valid and do not make check
                    if(!IsCheck(color))
                    {
                        //detecting move en passant and get piece out
                        if(m_board[dRow][dCol]->GetPiece() == 'P' && m_board[sRow][dCol] != NULL && m_board[sRow][dCol]->GetFlag() == 2)
                        {
                            delete m_board[sRow][dCol];
                            m_board[sRow][dCol] = NULL;
                        }
                        delete tmp;
                    }
                    else
                    {       //restore the move back
                            m_board[sRow][sCol] = m_board[dRow][dCol];
                            m_board[dRow][dCol] = tmp;
                            m_board[sRow][sCol]->SetFlag(oldFlag);
                            cout << "!! You are in check, can not move" << endl;
                            return false;
                    }
                }
                else
                {
                    cout << "!! The move is not valid. See instruction for help" << endl;
                    return false;
                }
            }
            else
            {
                cout << "!! Invalid choosen piece. See instruction for help" << endl;
            return false;
            }
            return true;

    }

    void CBoard::Clear()
    {
        cin.clear();
        while( cin.peek() != '\n' ) //release buffer
        {
            cin.get();
        }
    }
