#include "simulator.h"
#include <format>
#include <cmath>


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
    return true;
}

/**
called by the base class when the application has made contact with
the MOOSDB and a channel has been opened. Place code to specify what
notifications you want to receive here.
**/
bool CSimulator::OnConnectToServer()
{
    return true;
}

/** Called by the base class periodically. This is where you place code
which does the work of the application.
**/
bool CSimulator::Iterate()
{
    static int k = 0;

    if (k++%10 == 0)
    {
        //simulate some brownian motion
        static double dfHeading = 0;
        dfHeading += MOOSWhiteNoise(0.1);

        //publish the data (2nd param is a double so it will be forever double data...)
        m_Comms.Notify("Heading", dfHeading, MOOSTime());
    }
    
    if (k%35 == 0)
        {
            static double dfVolts = 100;
            dfVolts -= fabs(MOOSWhiteNoise(0.1));
            std::string sStatus = std::format("Status={},BatteryVoltage={:.2f},Bilge={}",
                        dfVolts > 50.0 ? "Good" : "Bad",
                        dfVolts,
                        k%100 > 50 ? "On" : "Off");

            //publish the data (2nd param is a std:: string so it will be forever string data...)
            m_Comms.Notify("VehicleStatus", sStatus, MOOSTime());
        }

        return true;
}

/** Called by the base class before the first ::Iterate is called. Place
startup code here - especially code which reads configuration data from the
mission file.
**/
bool CSimulator::OnStartUp()
{
    //here we extract the vehicle name...
    m_sVehicleName = "UnNamed";
    if (!m_MissionReader.GetConfigurationParam("VehicleName", m_sVehicleName))
        MOOSTrace(std::format("Warning parameter \"VehicleName\" not specified. Using default of \"{}\"\n",
            m_sVehicleName));

    //here we extract a vector of doubles from the configuration file
    std::vector vInitialLocation(3, 0.0);
    int nRows = vInitialLocation.size();
    int nCols = 1;

    if (!m_MissionReader.GetConfigurationParam("InitialLocation", vInitialLocation, nRows, nCols))
        MOOSTrace(std::format("Warning parameter \"InitialLocation\" not specified. Using default of \"{}\"\n",
            DoubleVector2String(vInitialLocation)));

    //here we extract a more complicated compound string parameter
    std::string sComplex;
    if (m_MissionReader.GetConfigurationParam("InitialConditions", sComplex))
    {
        MOOSTrace(std::format("InitialConditions string: {}\n", sComplex));

        //OK now we can suck out individual parameters from sComplex

        //what is the initial Bilge condition status?
        m_sBilge = "Off";
        MOOSValFromString(m_sBilge, sComplex, "Bilge");

        //what is the initial battery Voltage?
        m_dfBatteryVoltage = 100.0;
        MOOSValFromString(m_dfBatteryVoltage, sComplex, "BatteryVoltage");

        //what is the initial heading?
        m_dfHeading = 0;
        MOOSValFromString(m_dfHeading, sComplex, "Heading");
    }
    else
    {
        //bad news - this one is compulsory for this application...
        return MOOSFail("no \"InitialConditions\" specified in mission file (compulsory)\n");
    }

    MOOSTrace("Verbose Summary:\n");
    MOOSTrace(std::format("\tVehicle is called : {}\n", m_sVehicleName));
    MOOSTrace(std::format("\tInitial Location is  : {}\n", DoubleVector2String(vInitialLocation)));
    MOOSTrace(std::format("\tHeading is: {}\n", m_dfHeading));
    MOOSTrace(std::format("\tBatteryVoltage is: {}\n", m_dfBatteryVoltage));
    MOOSTrace(std::format("\tBilge is: {}\n", m_sBilge));



    return true;
}


























