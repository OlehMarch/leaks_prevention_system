#define pin_led1 7 // for WaterSensor1
#define pin_led2 8 // for WaterSensor2
#define pin_led3 6 // for WaterSensor3
#define pin_led4 5
#define pin_sound 4
#define pin_relay 0
#define pin_water_sensor1 1
#define pin_water_sensor2 2
#define pin_water_sensor3 3
#define pin_button1 9  // open valve
#define pin_button2 10 // close valve
#define pin_button3 11 // reset

#define led1_on digitalWrite(pin_led1, HIGH)
#define led2_on digitalWrite(pin_led2, HIGH)
#define led3_on digitalWrite(pin_led3, HIGH)
#define led4_on digitalWrite(pin_led4, HIGH)
#define led1_off digitalWrite(pin_led1, LOW)
#define led2_off digitalWrite(pin_led2, LOW)
#define led3_off digitalWrite(pin_led3, LOW)
#define led4_off digitalWrite(pin_led4, LOW)
#define relay_on digitalWrite(pin_relay, HIGH)
#define relay_off digitalWrite(pin_relay, LOW)
#define sound_on digitalWrite(pin_sound, LOW)
#define sound_off digitalWrite(pin_sound, HIGH)

#define water_sensor_1_state digitalRead(pin_water_sensor1) // 1(0) - off(on)
#define water_sensor_2_state digitalRead(pin_water_sensor2)
#define water_sensor_3_state digitalRead(pin_water_sensor3)
#define button1_state digitalRead(pin_button1)
#define button2_state digitalRead(pin_button2)
#define button3_state digitalRead(pin_button3)

#define OPENED true
#define CLOSED false
bool valveState;

void setup()
{
  valveState = OPENED;
  
  pinMode(pin_led1, OUTPUT);
  pinMode(pin_led2, OUTPUT);
  pinMode(pin_led3, OUTPUT);
  pinMode(pin_led4, OUTPUT);
  pinMode(pin_sound, OUTPUT);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_water_sensor1, INPUT);
  pinMode(pin_water_sensor2, INPUT);
  pinMode(pin_water_sensor3, INPUT);
  pinMode(pin_button1, INPUT);
  pinMode(pin_button2, INPUT);
  pinMode(pin_button3, INPUT);

  sound_off;
}

void waterSpilledSoundSignal()
{
  for (int i = 1; i <= 60; i++)
  {
    sound_on;
    delay(500);
    sound_off;
    delay(500);
  }
}

void checkTheSpillOfWater()
{
  if (water_sensor_1_state == 0)
  {
    if (valveState != CLOSED) relay_on;
    led1_on;
    valveState = CLOSED;
    
    // TODO: start in another thread sound for 1 min
    //waterSpilledSoundSignal();
  }
  else
  {
    led1_off;
  }
  if (water_sensor_2_state == 0)
  {
    if (valveState != CLOSED) relay_on;
    led2_on;
    valveState = CLOSED;
    
    // TODO: start in another thread sound for 1 min
    //waterSpilledSoundSignal();
  }
  else
  {
    led2_off;
  }
  if (water_sensor_3_state == 0)
  {
    if (valveState != CLOSED) relay_on;
    led3_on;
    valveState = CLOSED;
    
    // TODO: start in another thread sound for 1 min
    //waterSpilledSoundSignal();
  }
  else
  {
    led3_off;
  }
}

void checkButtonClick()
{
  if (button1_state == 1)
  {
    relay_off;
    valveState = OPENED;
    
    for (short i = 1; i <= 3; i++)
    {
      sound_on;
      delay(250);
      sound_off;
      delay(250);  
    }
  }
  if (button2_state == 1)
  {
    relay_on;
    valveState = CLOSED;
    
    sound_on;
    delay(1500);
    sound_off; 
  }
  if (button3_state == 1)
  {
    led1_off;
    led2_off;
    led3_off;
    sound_off;
    
    sound_on;
    delay(250);
    sound_off; 
  }
}

void checkValveState()
{
  if (valveState)
  {
    led4_off;
  }
  else
  {
    led4_on;
  }
}

void loop()
{
  checkValveState();
  checkTheSpillOfWater();
  checkButtonClick();
}
