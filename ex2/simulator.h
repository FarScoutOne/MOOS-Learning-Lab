// Ex1/simple_app.h: interface for the CSimpleApp class.

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <MOOS/libMOOS/MOOSLib.h>

class CSimulator : public CMOOSApp
{
public:
    //standard construction and destruction
    CSimulator();
    virtual ~CSimulator();

protected:
    //where we handle new mail
    bool OnNewMail(MOOSMSG_LIST& NewMail);
    //where we do the work
    bool Iterate();
    //called when we connect to the server
    bool OnConnectToServer();
    //called when we are starting up..
    bool OnStartUp();

    //state our interest in variables
    void DoRegistrations();

    // we'll call this if/when we receive a vehicle status message
    bool OnVehicleStatus(CMOOSMsg& Msg);

    // we'll call this if/when we receive a heading message
    bool OnHeading(CMOOSMsg& Msg);
};

#endif
