#pragma once

class TimeRun_Linear{
public:
    TimeRun_Linear() : STORED_TIME(-1){}

    void calculate(double distance){
        STORED_TIME = (distance / CAR_A + CAR_B)*1000;
    }
    double getTimeRun(){
        return STORED_TIME;
    }

private:
    const double CAR_A = 0.5657;
    const double CAR_B = 0.000007;

    double STORED_TIME;
};