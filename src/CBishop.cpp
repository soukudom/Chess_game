#include "CBishop.h"
#include <iostream>
    CBishop::CBishop(char color)
    {
        m_type = 'B';
        m_flag = 0;
        m_color = color;
    }

    CBishop::~CBishop()
    {

    }

    bool CBishop::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];
        int rowWay,colWay, checkRow, checkCol;

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {
            return false;
        }
        else
        {   //if the move make sense will be to forward or to back
            if( ( dstRow - srcRow == dstCol - srcCol ) || ( dstRow - srcRow == srcCol - dstCol ) )
            {
                if(dstRow - srcRow > 0)
                    rowWay = 1;
                else
                    rowWay = -1;

                if(dstCol - srcCol > 0)
                    colWay = 1;
                else
                    colWay = -1;
                //check if the way is clear
                for(checkRow = srcRow + rowWay, checkCol = srcCol + colWay; checkRow != dstRow; checkRow += rowWay, checkCol += colWay)
                {
                    if( board[checkRow][checkCol] != NULL )
                    {
                        return false;
                    }
                }

                return true;
            }
            else
                return false;
        }

    }


    char CBishop::GetPiece() const
    {
        return m_type;
    }

    char CBishop::GetColor() const
    {
        return m_color;
    }

    int CBishop::GetFlag() const
    {
        return m_flag;
    }

    void CBishop::SetFlag(int flag)
    {
        m_flag = flag;
    }
