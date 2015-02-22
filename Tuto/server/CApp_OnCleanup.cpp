//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {

    delete tcplistener;
    delete tcpclient;

    SDL_FreeSurface(Surf_Grid);
    SDL_FreeSurface(Surf_X);
    SDL_FreeSurface(Surf_O);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

//==============================================================================

