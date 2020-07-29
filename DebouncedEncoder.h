#ifndef __DEBOUNCED_ENCODER_H__
#define __DEBOUNCED_ENCODER_H__

#include "Arduino.h"

class DebouncedEncoder {
protected:
    typedef void (*CallbackFunction) (DebouncedEncoder&);
    CallbackFunction right_cb = NULL;
    CallbackFunction left_cb = NULL;
    int pinA;
    int pinB;
    int flag;
    int lastB;
public:
    DebouncedEncoder(int pa, int pb) : pinA(pa), pinB(pb), flag(false), lastB(HIGH), left_cb(NULL), right_cb(NULL) { 
        pinMode(pinA, INPUT_PULLUP);
        pinMode(pinB, INPUT_PULLUP);
    }

    void setLeftRotationHandler(CallbackFunction f) {
        left_cb = f;
    }

    void setRightRotationHandler(CallbackFunction f) {
        right_cb = f;
    }

    void loop() {
    	while (true) {
	        int a = digitalRead(pinA);
	        int b = digitalRead(pinB);

            if (flag == false && a == LOW) {
	            lastB = b;
	            flag = true;
	        }
	        if (flag == true && a == HIGH) {
	            if (b == HIGH && lastB == LOW) {
	                if (right_cb != NULL) right_cb(*this);
	            }
	            if (b == LOW && lastB == HIGH) {
	                if (left_cb != NULL) left_cb(*this);
	            }
	            flag = false;
	        }

	        if (!flag) break;
        }
    }
};


#endif
