#include "CPawn.h"
#include <iostream>


    CPawn::CPawn(char color)
    {
        m_type = 'P';
        m_flag = 0;
        m_color = color;
    }

    CPawn::~CPawn()
    {

    }

    bool CPawn::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {
            return false;
        }

        else
        {
            //move for empty destination
            if(p_pom == NULL)
            {
                if(srcCol == dstCol)
                {
                    return Classic(srcRow, srcCol, dstRow, dstCol, board);
                }
                //en passant move
                else if ( ( srcCol - 1 == dstCol ) || ( srcCol + 1 == dstCol ) )
                {
                    if ( board[srcRow][dstCol] == NULL )
                    {
                        return false;
                    }
                    return EnPassant(srcRow,srcCol,dstRow,dstCol,board);
                }

                else
                {
                    return false;
                }
            }

            else //if destination is not empty
            {
                if( (srcCol - 1 == dstCol) || (srcCol + 1 == dstCol ) )
                {
                    return Attack(srcRow, srcCol, dstRow, dstCol);
                }
                else
                {
                    return false;
                }
            }

        }
    }

    char CPawn::GetPiece() const
    {
        return m_type;
    }


    char CPawn::GetColor() const
    {
        return m_color;
    }

    int CPawn::GetFlag() const
    {
        return m_flag;
    }

    void CPawn::SetFlag(int flag)
    {
        m_flag = flag;
    }

    bool CPawn::EnPassant(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8])
    {

        if( GetColor() == 'W' )
        {

            if ( srcRow - 1 == dstRow && ( board[srcRow][dstCol]->GetFlag() == 2 ) )
            {
                return true;

            }
            else
            {
                return false;
            }
        }
        else
        {
            if ( srcRow + 1 == dstRow && ( board[srcRow][dstCol]->GetFlag() == 2 ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }

    bool CPawn::Attack(int srcRow, int srcCol, int dstRow, int dstCol)
    {
        if(GetColor() == 'W')
        {
            if( srcRow - 1 == dstRow )
            {
                m_flag = 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if( srcRow + 1 == dstRow )
            {
                m_flag = 1;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool CPawn::Classic(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8])
    {
        if(GetColor() == 'W')
        {
            if( srcRow - 1 == dstRow )
            {
                m_flag = 1;
                return true;
            }
            //first move
            else if ( m_flag == 0 && srcRow - 2 == dstRow )
            {
                if(board[srcRow-1][srcCol] == NULL)
                {
                    m_flag = 2;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else //black piece
        {
            if( srcRow + 1 == dstRow )
            {
                m_flag = 1;
                return true;
            }
            else if (m_flag == 0 && srcRow + 2 == dstRow)
            {
                if(board[srcRow+1][srcCol] == NULL)
                {
                    m_flag = 2;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

    }
