enum MODE{
    //Run the Whole program
    RUN = 0,
    //Test the Chemical Reaction (No Motor)
    TEST = 1,
    //Test the Relay with 1-2 Delay
    PULSE = 2,
    //TEST DATA Calibration curve
    CURVE = 4,
    //JUST RELAY
    RELAY = 5
};

struct PINS{

};


void setPins();
