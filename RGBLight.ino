#include <IRremote.h>
//#include "map.h"

int redPin = 13;
int greenPin = 12;
int bluePin = 11;

int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);
decode_results results;

//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

void setup()
{
	Serial.begin(9600);
	// In case the interrupt driver crashes on setup, give a clue
	// to the user what's going on.
	Serial.println("Enabling IRin");
	irrecv.enableIRIn(); // Start the receiver
	Serial.println("Enabled IRin");

	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);

  setColor(255, 0, 0);  // red
}

void loop()
{
	if (irrecv.decode(&results)) {
		if(results.decode_type == NEC) {
			Serial.println(results.value, HEX);
			remoteToColor(results.value);
		}
		irrecv.resume(); // Receive the next value
	}
	// delay(100);
}

void remoteToColor(unsigned long value)
{
    if(value == 16750695) {
			Serial.println("Red");
      setColor(255, 0, 0);//Red
    } else if(value == 16771095) {
			Serial.println("Red1");
      setColor(255, 100, 0);//Red1      
    } else if(value == 16767015) {
			Serial.println("Green");
      setColor(0, 255, 0);//Green
    } else if(value == 16730295) {
			Serial.println("Green1");
      setColor(0, 255, 126);//Green1
    } else if (value == 16746615) {
			Serial.println("Blue");
      setColor(0,0,255);//Blue
    } else if (value == 16738455) {
			Serial.println("Blue1");
      setColor(55, 92, 229);//Blue1
    }
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
#endif
	analogWrite(redPin, red);
	analogWrite(greenPin, green);
	analogWrite(bluePin, blue);
}
