#ifndef ALERTSOUND_H
#define ALERTSOUND_H

class AlertSound{
    public:
    AlertSound(int buzzle_pin, unsigned long SoundDelay);
    void Warning_alert();
    void Succsess_alert();

    private:
    int buzzle_pin;
    unsigned long SoundDelay;


};

#endif