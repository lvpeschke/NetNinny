/* tcp_layer.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "tcp_layer.h"

CTCPBuffer::CTCPBuffer ( int socket )
{
    m_Socket = socket;
    m_MaximalPos = 0;
    m_CurrentPos = 0;
}

char CTCPBuffer::getNextChar ( )
{
    if (m_CurrentPos == m_MaximalPos) {
        m_MaximalPos = recv(m_Socket, m_Buffer, BUFFERSIZE, 0);
        if (!m_MaximalPos)
            throw CSocketException(CONNECTION_CLOSED);
        m_CurrentPos = 0;
    }
    return m_Buffer[m_CurrentPos++];
}

void CTCPBuffer::getHTTPHeader ( string & header )
{
    // Finite state machine to analyze the header's content
    header.clear( );
state_0:
    header.push_back(getNextChar());
    if (*header.rbegin() == '\r')
        goto state_1;
    else
        goto state_0;
state_1:
    header.push_back(getNextChar());
    if (*header.rbegin() == '\n')
        goto state_2;
    else if (*header.rbegin() == '\r')
        goto state_1;
    else
        goto state_0;
state_2:
    header.push_back(getNextChar());
    if (*header.rbegin() == '\r')
        goto state_3;
    else
        goto state_0;
state_3:
    header.push_back(getNextChar());
    if (*header.rbegin() == '\n')
        return;
    else if (*header.rbegin() == '\r')
        goto state_1;
    else
        goto state_0;
}

void CTCPBuffer::getHTTPContent ( string & content, int content_length )
{
    content.clear();
    for (int i = 0; i<content_length; i++)
        content.push_back(getNextChar());
}
