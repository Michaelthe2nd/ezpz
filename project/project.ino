//***************************
//Libraries
#include <LiquidCrystal.h>
#include <Servo.h>
//***************************

Servo servo; //Defining servo's name
//***************************
// defines pins numbers
const int trigPin1 = 6;
const int echoPin1 = 7;
const int trigPin2 = 13;
const int echoPin2 = 10;
int servoPin = 8;
LiquidCrystal lcd(2, 3, 4, 11, 12, 5);
//***************************

int counter = 5; //Counting garage's empty places
//***************************
//Defining servo's positions.
int BarLow = 67;
int BarUp = 160;
//***************************
//Variable
int b = 0;
//***************************
//Defining variables for the Ultrasonic Sensor
float duration1;
float distance1;
float duration2;
float distance2;
//***************************


void setup() {
  lcd.begin(16, 2);//Starting LCD 16x2
  lcd.setCursor(0, 0);
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);//attaches servo to pin 8
  servo.write(BarLow);//Barrier is closed
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT

  Serial.begin(9600); // Starts serial communication
}


void loop()
{
  //*********Calculating distance on entrance sensor **********

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds

  distance1 = duration1 * 0.034 / 2; // Calculating the distance
  //*********finished calculating distance on entrance sensor **********

  //*********calculating distance on exit sensor **********


  //*********finished calculating distance on exit sensor **********
  b = 0;
  while ((distance1 < 5 || distance 2 < 5) && counter != 0) //while distance is lower than 5 AND counter is different than 0
  {
    servo.write(BarUp); //Barrier opens
    //*********Calculating distance on entrance sensor(in loop)**********
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = duration1 * 0.034 / 2;
    //*********finished calculating distance on entrance sensor(in loop)**********

    //*********calculating distance on exit sensor(in loop)**********
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = duration2 * 0.034 / 2;
    //*********finished calculating distance on entrance sensor(in loop)**********

    if (distance1 < 5 || b == 0) //Still in the while loop - making sure the decreasement of counter happens once.
    {
      b = 1;
      counter--;//Decreases the counter value by 1
    }

    if (distance2 < 5 || b == 0)//Still in the while loop - making sure the increasement of counter happens once.
    {
      b = 1;
    }

  } //Exitting while loop.


  if (counter == 0)
  {
    lcd.println("GARAGE IS FULL!");
  }
  servo.write(BarLow);//Closes garage
  Serial.print("Distance: ");
  Serial.println(distance);//prints the value of distance in cm
  delay(1500);
  Serial.print("Counter: ");
  Serial.println(counter);//prints the value of counter
  delay(1500);
}



