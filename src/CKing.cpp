#include "CKing.h"
#include <iostream>

    CKing::CKing(char color)
    {
        m_type = 'K';
        m_flag = 0;
        m_color = color;
    }

    CKing::~CKing()
    {


    }

    bool CKing::IsValidMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8])
    {
        CPiece * p_pom = board[dstRow][dstCol];

        //checking move to the same color place
        if( p_pom != NULL && GetColor() == p_pom->GetColor() )
        {

            return false;
        }
        else
        {
            //checking for castling
            if( ( dstRow == srcRow ) && ( dstCol - srcCol == -2 || dstCol - srcCol == 2) )
            {
                if( GetColor() == 'W' )
                {
                    return CastlingMove( srcRow, srcCol, dstRow, dstCol, board , 'W');
                }
                else //castling for black piece
                {
                    return CastlingMove( srcRow, srcCol, dstRow, dstCol, board , 'B');
                }
            }

            //checking normal move
            else if( ( ( dstRow - srcRow <= 1 ) && ( dstRow - srcRow >= -1 ) ) && ( ( dstCol - srcCol <= 1 ) && ( dstCol - srcCol >= -1 ) ) )
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

    char CKing::GetPiece() const
    {
        return m_type;
    }

    char CKing::GetColor() const
    {
        return m_color;
    }

    int CKing::GetFlag() const
    {
        return m_flag;
    }

    void CKing::SetFlag(int flag)
    {
        m_flag = flag;
    }

    bool CKing::IsSafety(CPiece * board [8][8], char color, int sRow, int sCol) const
    {
    int oldFlag;
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                if(board[row][col] != NULL)
                {
                    if( board[row][col]->GetColor() != color )
                    {
                        oldFlag = board[row][col]->GetFlag();
                        if( board[row][col]->IsValidMove( row,col, sRow, sCol, board ) )
                        {
                            return false;
                        }
                         board[row][col]->SetFlag(oldFlag);
                    }
                }
            }
        }
        return true;
    }

    bool CKing::CastlingMove(int srcRow, int srcCol, int dstRow, int dstCol, CPiece * board [8][8], char color)
    {
        int r;
        if(color == 'W')
            r = 7;
        else
            r = 0;
        //castling to the left
        if( ( dstCol - srcCol == -2 ) && ( m_flag == 0 ) && ( board[r][0] != NULL ) &&( board[r][0]->GetPiece() == 'R' ) && ( board[r][0]->GetFlag() == 0 ) )
        {   //checking if area between rook and king are empty
            if(board[srcRow][srcCol-1] != NULL || board[srcRow][srcCol-2] != NULL || board[srcRow][srcCol-3] != NULL )
            {
                return false;
            }
            else
            { //checking if places in king movement is safety
                if ( IsSafety(board,color,srcRow, srcCol) && IsSafety(board,color,srcRow,srcCol-1) && IsSafety(board,color,srcRow,srcCol-2) )
                {
                    m_flag = 4;
                    return true;
                }
                else
                {
                    return false;
                }
            }

        }//castling to the right
        else if( ( dstCol - srcCol == 2 ) && ( m_flag == 0 ) && ( board[r][7] != NULL ) &&( board[r][7]->GetPiece() == 'R' ) && ( board[r][7]->GetFlag() == 0 ) )
        {
            if(board[srcRow][srcCol+1] != NULL || board[srcRow][srcCol+2] != NULL )
            {
                return false;
            }
            else
            {
                if ( IsSafety(board,color,srcRow, srcCol) && IsSafety(board,color,srcRow,srcCol+1) && IsSafety(board,color,srcRow,srcCol+2) )
                {
                    m_flag = 4;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
