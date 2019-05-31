
 #include <blynk.h> //include the Blynk library



char auth[] = "0b5ace572fde4a66bd720bd596782688"; //NOTE: This needs to be updated with your own unique authentication code
                                                  // from the Blynk app for this to work.

const int btnPin = D3;             // pin for physical push button switch.
const int LEDPin = D1;         // pin for LED output.

BlynkTimer timer;
void checkPhysicalButton();
int btnPinState = LOW;           // ON
int LEDPinState = HIGH;        // OFF

//*******Sets LED to Off Position*****************
#define TURN_ON 0                 // TURN_ON and TURN_OFF are defined
#define TURN_OFF 1                // Used to switch LED states

void setup()
{
  Serial.begin (9600);
  Blynk.begin(auth);
  pinMode(LEDPin, OUTPUT);            //  initialize your pin as output.
  pinMode(btnPin, INPUT_PULLUP);        //  initialize your pin as input with enable internal pull-up resistor "input_pullup"
  digitalWrite(LEDPin, LEDPinState);
  digitalWrite(LEDPin, TURN_OFF);     // remain off till command is receive

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

// Every time we connect to the cloud...
BLYNK_CONNECTED()
{
  // Request the latest state from the server
  Blynk.syncVirtual(V1);
}

// When App button is pushed - switch the state
// Map this Virtual Pin to your Mobile Blynk apps widget.
BLYNK_WRITE(V1)
{
  LEDPinState = param.asInt();
  digitalWrite(LEDPin, LEDPinState);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW)
  {
    // btnPinState is used to avoid sequential toggles
    if (btnPinState != LOW)
    {
      // Toggle LED state
      LEDPinState = !LEDPinState;
      digitalWrite(LEDPin, LEDPinState);
      Blynk.virtualWrite(V1, LEDPinState);
      Blynk.notify("Hello! Thinking of You! SIT210");  //Update button widget
    }

    btnPinState = LOW;
  }
  else
  {
    btnPinState = HIGH;
  }
}

void loop()
{
  Blynk.run();                               // Run Blynk
  timer.run();                               // Run SimpleTimer
}
