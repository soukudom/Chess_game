#include "CRook.h"
#include <iostream>

    CRook::CRook(char color)
    {
        m_type = 'R';
        m_flag = 0;
        m_color = color;

    }

    CRook::~CRook()
    {

    }

    bool CRook::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];
        int way,checkItem;

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {
            return false;
        }
        else
        {
            if( srcCol == dstCol )
            {
                //check if the move will be to forward or to back
                if(dstRow-srcRow > 0)
                    way = 1;
                else
                    way = -1;
                //check if the way is clear
                for(checkItem = srcRow+way; checkItem != dstRow; checkItem += way)
                {
                    if( board[checkItem][srcCol] != NULL )
                        return false;
                }
                m_flag = 1;
                return true;
            }
            else if(srcRow == dstRow)
            {
                if( dstCol-srcCol > 0 )
                    way = 1;
                else
                    way = -1;

                for( checkItem = srcCol+way; checkItem != dstCol; checkItem += way )
                {
                    if(board[srcRow][checkItem] != NULL)
                        return false;
                }
                m_flag = 1;
                return true;
            }
            else
                return false;
        }

    }

    char CRook::GetPiece() const
    {

        return m_type;
    }

    char CRook::GetColor() const
    {
        return m_color;
    }

    int CRook::GetFlag() const
    {
        return m_flag;
    }

    void CRook::SetFlag(int flag)
    {
        m_flag = flag;

    }
