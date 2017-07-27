#include "CQueen.h"
#include "CRook.h"
#include <iostream>

    CQueen::CQueen(char color)
    {
        m_type = 'Q';
        m_flag = 0;
        m_color = color;
    }

    CQueen::~CQueen()
    {

    }

    bool CQueen::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {
            return false;
        }

        else
        {
            return Classic(srcRow, srcCol, dstRow, dstCol, board);
        }
    }

    char CQueen::GetPiece() const
    {
        return m_type;
    }

    char CQueen::GetColor() const
    {
        return m_color;
    }

    int CQueen::GetFlag() const
    {
        return m_flag;
    }

    void CQueen::SetFlag(int flag)
    {
        m_flag = flag;
    }

    bool CQueen::Classic(int srcRow, int srcCol, int dstRow, int dstCol, CPiece *board[8][8])
    {
        int rowWay, colWay,checkRow, checkCol;
        if( srcCol == dstCol )
        {
            //if the move will be to forward or to back
            if(dstRow-srcRow > 0)
                rowWay = 1;
            else
                rowWay = -1;

            //check if the way is empty
            for(checkRow = srcRow+rowWay; checkRow != dstRow; checkRow += rowWay )
            {
                if( board[checkRow][srcCol] != NULL )
                    return false;
            }
            return true;
        }
        else if(srcRow == dstRow)
        {
            if( dstCol-srcCol > 0 )
                colWay = 1;
            else
                colWay = -1;

            for( checkCol = srcCol + colWay; checkCol != dstCol; checkCol += colWay )
            {
                if(board[srcRow][checkCol] != NULL)
                    return false;
            }
            return true;

        }

    //diagonal move
        else if( ( dstRow - srcRow == dstCol - srcCol ) || ( dstRow - srcRow == srcCol - dstCol ) )
        {
            if(dstRow - srcRow > 0)
                rowWay = 1;
            else
                rowWay = -1;

            if(dstCol - srcCol > 0)
                colWay = 1;
            else
                colWay = -1;

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

