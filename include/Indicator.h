#ifndef INDICATOR_H
#define INDICATOR_H

class Indicator {
    public:
    int success();
    int error();
    int Delay_warning = 100;  
    int Delay_success = 1000;
    int warning_led = 13;
    int success_led = 12;

};



#endif