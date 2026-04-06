// ex2/simulator.h: interface for the CSimulator class.

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <MOOS/libMOOS/MOOSLib.h>
#include <string>

class CSimulator : public CMOOSApp
{
public:
    CSimulator() = default;
    virtual ~CSimulator() = default;

protected:
    // where we handle new mail
    bool OnNewMail(MOOSMSG_LIST& NewMail);
    // where we do the work
    bool Iterate();
    // called when we connect to the server
    bool OnConnectToServer();
    // called when we are starting up
    bool OnStartUp();

private:
    // vehicle configuration read from mission file
    std::string m_sVehicleName;
    std::string m_sBilge;

    // vehicle state
    double m_dfHeading;
    double m_dfBatteryVoltage;
};

#endif