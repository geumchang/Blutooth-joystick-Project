#include <SoftwareSerial.h>
// BUTTON.PIN
#define THIRD_BUTTON      2
#define SECOND_BUTTON     3
#define FIRST_BUTTON      4
#define BLIND_BUTTON      5
#define ENTER_STATE       6
#define PREVIOUS_BUTTON   7

// JOYSTICK.PIN
#define JOYSTICK_LEFT  	9 	
#define JOYSTICK_RIGHT 	8 
#define JOYSTICK_UP    10
#define JOYSTICK_DOWN  11

// TX.PIN, RX.PIN
#define TX 12
#define RX 13

// Button_information
#define BUTTON_NUMBER 10
#define BUTTON_PRESSED  0
#define BUTTON_RELEASED 1
#define GLITCH_PREVENTION_DELAY 60
#define DATA_TRANSMISSION_DELAY 50

unsigned char button_current_status[BUTTON_NUMBER] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};
int get_button(int button_pin);
int button_check(void);
SoftwareSerial bluetooth(RX, TX);

void setup() {
  bluetooth.begin(9600);
  pinMode(PREVIOUS_BUTTON, INPUT);
  pinMode(ENTER_STATE, INPUT);
  pinMode(BLIND_BUTTON, INPUT);
  pinMode(FIRST_BUTTON, INPUT);
  pinMode(SECOND_BUTTON, INPUT);
  pinMode(THIRD_BUTTON, INPUT);
  pinMode(JOYSTICK_LEFT, INPUT);
  pinMode(JOYSTICK_RIGHT, INPUT);
  pinMode(JOYSTICK_UP, INPUT);
  pinMode(JOYSTICK_DOWN, INPUT);
}

void loop() {
  int button_key;

  if (button_key = button_check())
  {
    switch (button_key)
    {
      case FIRST_BUTTON:    {bluetooth.write('1'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case SECOND_BUTTON:   {bluetooth.write('2'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case THIRD_BUTTON:    {bluetooth.write('3'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case PREVIOUS_BUTTON: {bluetooth.write('5'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case BLIND_BUTTON:    {bluetooth.write('4'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case ENTER_STATE:     {bluetooth.write('6'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case JOYSTICK_LEFT:   {bluetooth.write('7'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case JOYSTICK_RIGHT: 	{bluetooth.write('8'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case JOYSTICK_UP:    	{bluetooth.write('9'); 	delay(DATA_TRANSMISSION_DELAY); break; }
      case JOYSTICK_DOWN:   {bluetooth.write('0'); delay(DATA_TRANSMISSION_DELAY); break; }
    }
  }
}

int get_button(int button_pin)
{
  int current_state;
  int button_num = button_pin-2;
  
  current_state = digitalRead(button_pin);
  if (current_state == BUTTON_PRESSED && button_current_status[button_num] == BUTTON_RELEASED)
  {
    delay(GLITCH_PREVENTION_DELAY);
    button_current_status[button_num] = BUTTON_PRESSED;
    return BUTTON_RELEASED;
  }
  else if (current_state == BUTTON_RELEASED && button_current_status[button_num] == BUTTON_PRESSED)
  {
    delay(GLITCH_PREVENTION_DELAY);
    button_current_status[button_num] = BUTTON_RELEASED;
    return BUTTON_PRESSED;
  }
  return BUTTON_RELEASED;
}

int button_check(void) {
  if      (get_button(THIRD_BUTTON) == BUTTON_PRESSED)    {return THIRD_BUTTON; }
  else if (get_button(SECOND_BUTTON) == BUTTON_PRESSED)   {return SECOND_BUTTON; }
  else if (get_button(FIRST_BUTTON) == BUTTON_PRESSED)    {return FIRST_BUTTON; }
  else if (get_button(BLIND_BUTTON) == BUTTON_PRESSED)    {return BLIND_BUTTON; }
  else if (get_button(ENTER_STATE) == BUTTON_PRESSED)     {return ENTER_STATE; }
  else if (get_button(PREVIOUS_BUTTON) == BUTTON_PRESSED) {return PREVIOUS_BUTTON; } 
  else if (get_button(JOYSTICK_LEFT) == BUTTON_PRESSED)   {return JOYSTICK_LEFT; }
  else if (get_button(JOYSTICK_RIGHT) == BUTTON_PRESSED)  {return JOYSTICK_RIGHT; }
  else if (get_button(JOYSTICK_UP) == BUTTON_PRESSED)     {return JOYSTICK_UP; }
  else if (get_button(JOYSTICK_DOWN) == BUTTON_PRESSED)   {return JOYSTICK_DOWN; }
  else {return 0; }
}
