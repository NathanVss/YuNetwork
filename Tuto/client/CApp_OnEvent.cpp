//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnExit() {
	Running = false;
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY) {
	int ID	= mX / 200;
	ID = ID + ((mY / 200) * 3);

	if(Grid[ID] != GRID_TYPE_NONE) {
		return;
	}

//Player == 0 will always be Server. Always starts to play and always be "X". So if CurrentPlayer is not zero,
//the game is necessarily connected
	if(CurrentPlayer != 0) {
		SetCell(ID, GRID_TYPE_O);
		CurrentPlayer = 0;
//Send a message to the server, telling the ID of the clicked cell
		msg.LoadByte((char) ID);
 		tcpclient->Send(msg);

	}
}

//==============================================================================

