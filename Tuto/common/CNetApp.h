//==============================================================================
#ifndef _NETAPP_H_
	#define _NETAPP_H_

#include "CNet.h"

//==============================================================================

class CNetMessageApp : public CNetMessage {
  private:
//Virtual function that indicates how many bytes may have to be loaded onto the object. Overrides the parent class function member to work with only a byte
    virtual int NumToLoad();

//Virtual function that indicates how many bytes may have to be downloaded from the object. Overrides the parent class function member to work with only a byte
    virtual int NumToUnLoad();

  public:
    void LoadByte(char);
    char UnLoadByte();
};

//==============================================================================

#endif

