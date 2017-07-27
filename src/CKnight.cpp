#include "CKnight.h"
#include <iostream>


    CKnight::CKnight(char color)
    {
        m_type = 'N';
        m_flag =  0;
        m_color = color;

    }

    CKnight::~CKnight()
    {

    }

    bool CKnight::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {
            return false;
        }
        else
        {
            if( ( dstRow == srcRow + 1 ) || ( dstRow == srcRow - 1 ) )
            {
                if( ( dstCol == srcCol + 2 )  || ( dstCol == srcCol - 2 ) )
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
                if( ( dstRow == srcRow + 2 ) || ( dstRow == srcRow - 2 ) )
                {
                    if( ( dstCol == srcCol + 1 ) || ( dstCol == srcCol - 1) )
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
                    return false;
                }
            }

        }
    }

    char CKnight::GetPiece() const
    {
        return m_type;
    }

    char CKnight::GetColor() const
    {
        return m_color;
    }

    int CKnight::GetFlag() const
    {
        return m_flag;
    }

    void CKnight::SetFlag(int flag)
    {
        m_flag = flag;
    }
