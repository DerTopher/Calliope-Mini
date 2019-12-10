#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;

void grundfunktionalitaet(double ___Welchetaste, double ___Modeswitchausgeloest, double ___Schuetteltest, double ___Zahler);

void resetfunktion();

double tastendruck(double ___x);

double schutteltestfunktion(double ___x2);

void gattermodus(double ___TastenvarGate, double ___Schuetteltestgate, double ___Gattermoduszaehler, double ___Negiert, double ___WahrheitswertUND, double ___WahrheitswerODER);

double und(double ___x3);

double oder(double ___x4);

double xOR(double ___x5);

void schaltermodus(double ___TastenvarSwitch, double ___SchuetteltestSwitch, double ___Schalterwert, double ___Anzeigemodus);

void ausgangsmodus(double ___TastenvarExit, double ___SchuetteltestExit, double ___WahrheitswerAusgang);



int main()
{
    _uBit.init();
    _uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    _uBit.accelerometer.updateSample();
    grundfunktionalitaet(0, 0, 0, 0);
    release_fiber();
}

void grundfunktionalitaet(double ___Welchetaste, double ___Modeswitchausgeloest, double ___Schuetteltest, double ___Zahler) {
    _uBit.sleep(500);
    while ( true ) {
        ___Welchetaste = tastendruck(0);
        ___Schuetteltest = schutteltestfunktion(0);
        if ( ___Modeswitchausgeloest == 0 ) {
            gattermodus(0, 0, 0, 0, 0, 0);
        }
        if ( ___Modeswitchausgeloest == 1 ) {
            schaltermodus(0, 0, 0, 0);
        }
        if ( ___Modeswitchausgeloest == 2 ) {
            ausgangsmodus(0, 0, 0);
        }
        if ( ___Modeswitchausgeloest == 3 ) {
            ___Modeswitchausgeloest = 0;
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
}

void resetfunktion() {
    _uBit.soundmotor.soundOn(261.626); _uBit.sleep(2000); _uBit.soundmotor.soundOff();
    _uBit.display.scroll(ManagedString("Reset"));
    _uBit.display.clear();
    _uBit.rgb.off();
    _uBit.sleep(200);
    grundfunktionalitaet(0, 0, 0, 0);
}

double tastendruck(double ___x) {
    ___x = 0;
    if ( _uBit.buttonA.isPressed() ) {
        _uBit.sleep(50);
        if ( _uBit.buttonB.isPressed() ) {
            _uBit.soundmotor.soundOn(311.127); _uBit.sleep(250); _uBit.soundmotor.soundOff();
            ___x = 3;
        } else {
            _uBit.soundmotor.soundOn(349.228); _uBit.sleep(250); _uBit.soundmotor.soundOff();
            ___x = 1;
        }
    }
    if ( _uBit.buttonB.isPressed() ) {
        _uBit.sleep(50);
        if ( _uBit.buttonA.isPressed() ) {
            _uBit.soundmotor.soundOn(311.127); _uBit.sleep(250); _uBit.soundmotor.soundOff();
            ___x = 3;
        } else {
            _uBit.soundmotor.soundOn(493.883); _uBit.sleep(250); _uBit.soundmotor.soundOff();
            ___x = 2;
        }
    }
    return ___x;
}

double schutteltestfunktion(double ___x2) {
    if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_SHAKE) ) {
        ___x2 = 1;
    } else {
        ___x2 = 0;
    }
    return ___x2;
}

void gattermodus(double ___TastenvarGate, double ___Schuetteltestgate, double ___Gattermoduszaehler, double ___Negiert, double ___WahrheitswertUND, double ___WahrheitswerODER) {
    _uBit.rgb.off();
    _uBit.sleep(50);
    _uBit.rgb.setColour(MicroBitColor(204, 102, 204, 255));
    _uBit.display.scroll(ManagedString("G8"));
    ___Gattermoduszaehler = 0;
    ___Negiert = 0;
    ___WahrheitswertUND = und(0);
    ___WahrheitswerODER = oder(0);
    while ( true ) {
        ___TastenvarGate = tastendruck(0);
        ___Schuetteltestgate = schutteltestfunktion(0);
        if ( ___TastenvarGate == 3 ) {
            grundfunktionalitaet(0, 1, 0, 0);
        }
        if ( ___Schuetteltestgate == 1 ) {
            resetfunktion();
        }
        if ( ___TastenvarGate == 1 ) {
            ___Gattermoduszaehler += 1;
            if ( ___Gattermoduszaehler == 3 ) {
                ___Gattermoduszaehler = 0;
            }
        }
        if ( ___TastenvarGate == 2 ) {
            ___Negiert += 1;
            if ( ___Negiert == 2 ) {
                ___Negiert = 0;
            }
        }
        if ( ( ___Gattermoduszaehler == 0 ) && ( ___Negiert == 0 ) ) {
            _uBit.display.print(MicroBitImage("0,255,0,0,0\n255,0,255,0,0\n0,255,255,0,255\n255,0,0,255,0\n0,255,255,0,255\n"));
            if ( und(0) == 1 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        if ( ( ___Gattermoduszaehler == 0 ) && ( ___Negiert == 1 ) ) {
            _uBit.display.print(MicroBitImage("255,255,255,255,255\n255,0,255,0,0\n0,255,255,0,255\n255,0,0,255,0\n0,255,255,0,255\n"));
            if ( und(0) == 0 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        if ( ( ___Gattermoduszaehler == 1 ) && ( ___Negiert == 0 ) ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,255,0,0,0\n255,0,255,255,255\n255,0,255,255,0\n0,255,0,255,0\n"));
            if ( oder(0) == 1 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        if ( ( ___Gattermoduszaehler == 1 ) && ( ___Negiert == 1 ) ) {
            _uBit.display.print(MicroBitImage("255,255,255,255,255\n0,255,0,0,0\n255,0,255,255,255\n255,0,255,255,0\n0,255,0,255,0\n"));
            if ( oder(0) == 0 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        if ( ( ___Gattermoduszaehler == 2 ) && ( ___Negiert == 0 ) ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n255,0,255,255,255\n0,255,0,255,0\n255,0,255,255,0\n"));
            if ( xOR(0) == 1 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        if ( ( ___Gattermoduszaehler == 2 ) && ( ___Negiert == 1 ) ) {
            _uBit.display.print(MicroBitImage("255,255,255,255,255\n0,0,0,0,0\n255,0,255,255,255\n0,255,0,255,0\n255,0,255,255,0\n"));
            if ( xOR(0) == 0 ) {
                _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
                _uBit.io.P1.setAnalogValue(1);
            } else {
                _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
                _uBit.io.P1.setAnalogValue(0);
            }
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
}

double und(double ___x3) {
    if ( _uBit.io.P12.isTouched() && _uBit.io.P0.isTouched() ) {
        ___x3 = 1;
    } else {
        ___x3 = 0;
    }
    return ___x3;
}

double oder(double ___x4) {
    if ( _uBit.io.P12.isTouched() || _uBit.io.P0.isTouched() ) {
        ___x4 = 1;
    } else {
        ___x4 = 0;
    }
    return ___x4;
}

double xOR(double ___x5) {
    if ( ( _uBit.io.P12.isTouched() && ! _uBit.io.P0.isTouched() ) || ( _uBit.io.P0.isTouched() && ! _uBit.io.P12.isTouched() ) ) {
        ___x5 = 1;
    } else {
        ___x5 = 0;
    }
    return ___x5;
}

void schaltermodus(double ___TastenvarSwitch, double ___SchuetteltestSwitch, double ___Schalterwert, double ___Anzeigemodus) {
    _uBit.rgb.off();
    _uBit.sleep(50);
    ___Anzeigemodus = 0;
    ___Schalterwert = 0;
    _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
    _uBit.display.scroll(ManagedString("S"));
    _uBit.sleep(500);
    _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,255,0,0\n0,255,255,255,0\n255,255,255,255,255\n0,0,0,0,0\n"));
    _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
    _uBit.sleep(500);
    _uBit.display.print(MicroBitImage("0,0,0,0,0\n255,255,255,255,255\n0,255,255,255,0\n0,0,255,0,0\n0,0,0,0,0\n"));
    _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
    _uBit.sleep(500);
    _uBit.display.clear();
    _uBit.rgb.off();
    while ( true ) {
        ___TastenvarSwitch = tastendruck(0);
        ___SchuetteltestSwitch = schutteltestfunktion(0);
        if ( ___TastenvarSwitch == 3 ) {
            grundfunktionalitaet(0, 2, 0, 0);
        }
        if ( ( _uBit.io.P12.isTouched() || _uBit.io.P1.isTouched() ) || _uBit.io.P16.isTouched() ) {
            _uBit.display.scroll(ManagedString("Pin1 = Ausgang"));
        }
        if ( ___SchuetteltestSwitch == 1 ) {
            resetfunktion();
        }
        if ( ___TastenvarSwitch == 1 ) {
            ___Schalterwert += 1;
            if ( ___Schalterwert == 2 ) {
                ___Schalterwert = 0;
            }
            _uBit.rgb.off();
        }
        if ( ___TastenvarSwitch == 2 ) {
            ___Anzeigemodus += 1;
            if ( ___Anzeigemodus == 3 ) {
                ___Anzeigemodus = 0;
            }
        }
        if ( ___Schalterwert == 0 ) {
            _uBit.sleep(50);
            _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
            _uBit.io.P0.setAnalogValue(0);
        }
        if ( ___Schalterwert == 1 ) {
            _uBit.sleep(50);
            _uBit.rgb.setColour(MicroBitColor(51, 255, 51, 255));
            _uBit.io.P0.setAnalogValue(1);
        }
        if ( ( ___Anzeigemodus == 0 ) && ( ___Schalterwert == 0 ) ) {
            _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,255,0,255,0\n0,255,0,255,0\n0,255,0,255,0\n0,0,255,0,0\n"));
        }
        if ( ( ___Anzeigemodus == 0 ) && ( ___Schalterwert == 1 ) ) {
            _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,255,255,0,0\n0,0,255,0,0\n0,0,255,0,0\n0,255,255,255,0\n"));
        }
        if ( ( ___Schalterwert == 1 ) && ( ___Anzeigemodus == 1 ) ) {
            _uBit.display.print(MicroBitImage("255,0,0,0,255\n255,0,255,0,255\n255,0,255,0,255\n255,0,255,0,255\n0,255,0,255,0\n"));
        }
        if ( ( ___Schalterwert == 0 ) && ( ___Anzeigemodus == 1 ) ) {
            _uBit.display.print(MicroBitImage("0,255,255,255,0\n0,255,0,0,0\n0,255,255,0,0\n0,255,0,0,0\n0,255,0,0,0\n"));
        }
        if ( ( ___Schalterwert == 1 ) && ( ___Anzeigemodus == 2 ) ) {
            _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,255,255,255,0\n255,255,255,255,255\n0,0,0,0,0\n0,0,0,0,0\n"));
        }
        if ( ( ___Schalterwert == 0 ) && ( ___Anzeigemodus == 2 ) ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n255,255,255,255,255\n0,255,255,255,0\n0,0,255,0,0\n"));
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
}

void ausgangsmodus(double ___TastenvarExit, double ___SchuetteltestExit, double ___WahrheitswerAusgang) {
    _uBit.rgb.off();
    _uBit.sleep(50);
    ___WahrheitswerAusgang = 0;
    _uBit.rgb.setColour(MicroBitColor(51, 51, 255, 255));
    _uBit.display.scroll(ManagedString("Exit"));
    while ( true ) {
        ___TastenvarExit = tastendruck(0);
        ___SchuetteltestExit = schutteltestfunktion(0);
        if ( ___TastenvarExit == 3 ) {
            grundfunktionalitaet(0, 3, 0, 0);
        }
        if ( ___SchuetteltestExit == 1 ) {
            resetfunktion();
        }
        if ( _uBit.io.P12.isTouched() ) {
            _uBit.display.print(MicroBitImage("255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n"));
        } else {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        }
        if ( ( _uBit.io.P0.isTouched() || _uBit.io.P1.isTouched() ) || _uBit.io.P16.isTouched() ) {
            _uBit.display.scroll(ManagedString("Pin0 = Eingang"));
        }
        _uBit.rgb.setColour(MicroBitColor(51, 51, 255, 255));
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
}
