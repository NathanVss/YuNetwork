//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnLoop() {
//if not connected, listen to the port to detect if there is a client waiting there
    if (!Connected) {
        if (tcplistener->Accept (*tcpclient)) {
            Connected = true;
        }
    }
    else {
//if connected, checks the socket for messages ready to be read
        if (tcpclient->Ready()) {
// if there is a message, try to receive it. In case of disconnection, the TCP protocol sends
// a message with no bytes
            if (tcpclient->Receive (msg)) {
                //if there is a valid message, we can set the grid and player status
                SetCell((int) msg.UnLoadByte(), GRID_TYPE_O);
                CurrentPlayer = 0;
            }
            else
                Connected = false;
        }
    }
}

//==============================================================================

