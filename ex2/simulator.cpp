#include "simulator.h"
#include <format>

// Use compiler generated default constructor and destructor
CSimulator::CSimulator() = default;
CSimulator::~CSimulator() = default;

/**
Called by base class whenever new mail has arrived.
Place your code for handling mail (notifications that something
has changed in the MOOSDB in this function

Parameters:
    NewMail: std::list<CMOOSMsg> reference

Return Value:
    return true if everything went OK
    return false if there was a problem
**/
//an alternative OnNewMail using PeekMail and checking for stale messages
bool CSimulator::OnNewMail(MOOSMSG_LIST &NewMail)
{
    CMOOSMsg Msg;
    double dfNow = MOOSTime();

    if (m_Comms.PeekMail(NewMail, "VehicleStatus", Msg, false, true))
    {
        if (!Msg.IsSkewed(dfNow))
        {
            OnVehicleStatus(Msg);
        }
    }

    if (m_Comms.PeekMail(NewMail, "Heading", Msg, false, true))
    {
        if (!Msg.IsSkewed(dfNow))
        {
            OnHeading(Msg);
        }
    }

    return true;
}

/**
called by the base class when the application has made contact with
the MOOSDB and a channel has been opened. Place code to specify what
notifications you want to receive here.
**/
bool CSimulator::OnConnectToServer()
{
    //do registrations
    DoRegistrations();

    return true;
}

/** Called by the base class periodically. This is where you place code
which does the work of the application.
**/
bool CSimulator::Iterate()
{
    return true;
}

/** Called by the base class before the first ::Iterate is called. Place
startup code here - especially code which reads configuration data from the
mission file.
**/
bool CSimulator::OnStartUp()
{
    //do registration - it's good practice to do this BOTH in OnStartUp and
    //in OnConnectToServer - that way if comms is lost registrations will be
    //reinstigated when the connection is remade
    DoRegistrations();

    return true;
}

bool CSimulator::OnVehicleStatus(CMOOSMsg& Msg)
{
    MOOSTrace(std::format("I ({}) received a notification about \"{}\" the details are:\n",
        GetAppName(),
        Msg.GetKey()));

    //if you want to see all the details you can print a message...
    //Msg.Trace();

    if (!Msg.IsString())
        return MOOSFail("Ouch - I was promised \"VehicleStatus\" would be a string!");

    //OK the guy who wrote the program that publishes VehicleStatus wrote me an
    //email saying the format of the message is:
    //Status = [Good/Bad/Sunk], BatteryVoltage = <double>, Bilge=[on/off]
    //so here we parse the bits we want from the string
    std::string sStatus = "Unknown";

    if (!MOOSValFromString(sStatus, Msg.GetString(), "Status"))
        MOOSTrace(std::format("warning field \"Status\" not found in VehicleStatus string {}",
            MOOSHERE));

    double dfBatteryVoltage = -1;
    if (!MOOSValFromString(dfBatteryVoltage, Msg.GetString(), "BatteryVoltage"))
        MOOSTrace(std::format("warning field \"BatteryVoltage\" not found in VehicleStatus string {}",
            MOOSHERE));

    //simple print out of our findings..
    MOOSTrace(std::format("Status is \"{}\" and battery voltage is {:.2f}V\n",
        sStatus,
        dfBatteryVoltage));

    return true;
}

bool CSimulator::OnHeading(CMOOSMsg& Msg)
{
    MOOSTrace(std::format("I {} received a notification about \"{}\" the details are:\n",
        GetAppName(),  //note the GetAppName() returns the name of this application as seen by the DB
        Msg.GetKey()));  //note GetKey() returns the name of the variable

    //if you want to see all the details you can print a message...
    //Msg.Trace();

    //you might want to be sure that the message is in the formate you were expecting
    //in this case heading comes as a single double...

    if (!Msg.IsDouble())
        return MOOSFail("Ouch - I was promised \"Heading\" would be a double %s", MOOSHERE);

    double dfHeading = Msg.GetDouble();
    double dfTime = Msg.GetTime();

    MOOSTrace(std::format("The heading (according to process {}), at time {} ({} since appstart) is {}\n",
        Msg.GetSource(), //who wrote it
        dfTime,  //when
        dfTime-GetAppStartTime(),  //time since we started running (easier to read)
        dfHeading));  //the actual heading

    return true;
}

void CSimulator::DoRegistrations()
{
    std::cout << "DoRegistrations called" << std::endl;

    //register to be told about every change (write) to "VehicleStatus"
    m_Comms.Register("VehicleStatus", 0);

    //register to be told about changes (writes) to "Heading" at most 4 times a second
    m_Comms.Register("Heading", 0.25);
}


























