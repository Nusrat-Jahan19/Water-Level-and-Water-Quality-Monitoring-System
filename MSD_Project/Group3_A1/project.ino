#include <LiquidCrystal.h>

#define trigger 10
#define echo 11
#define motor 8
#define buzzer 12
#define ledpinred  14
#define ledpingreen  15
#define pH_Sensor_Pin  A1
#define TDS_Sensor_Pin  A0

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float time = 0;
float distance = 0;
int temp = 0;
int sensorValue = 0;
float tdsValue = 0;
float Voltage = 0;

void setup()
{
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  pinMode(pH_Sensor_Pin, INPUT);
  pinMode(TDS_Sensor_Pin, INPUT);
  pinMode(ledpinred, OUTPUT);
  pinMode(ledpingreen, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.print("Water Level and");
  lcd.setCursor(0, 1);
  lcd.print("Water Quality");
  lcd.setCursor(0, 2);
  lcd.print(" Monitoring ");

  lcd.setCursor(0, 3);
  lcd.print(" System ");
  delay(1000);
}

void loop()
{
  lcd.clear();
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);
  distance = time * 340 / 200000;
  lcd.clear();
  lcd.print("Water Space In  ");
  lcd.setCursor(0, 1);
  lcd.print("Tank is:");
  lcd.print(distance);
  lcd.print("Cm");
  delay(1000);
  if (distance < 12 && temp == 0)
  {
    digitalWrite(motor, LOW);
    digitalWrite(buzzer, HIGH);
    lcd.clear();
    lcd.print("Water Tank Full ");
    lcd.setCursor(0, 1);
    lcd.print("Motor Turned OFF");
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    temp = 1;
  }

  else if (distance < 12 && temp == 1)
  {
    digitalWrite(motor, LOW);
    lcd.clear();
    lcd.print("Water Tank Full ");
    lcd.setCursor(0, 1);
    lcd.print("Motor Turned OFF");
    delay(1000);
  }

  else if (distance > 30)
  {
    digitalWrite(motor, HIGH);
    lcd.clear();
    lcd.print("LOW Water Level");
    lcd.setCursor(0, 1);
    lcd.print("Motor Turned ON");
    delay(1000);
    temp = 0;
  }


  float val = analogRead(pH_Sensor_Pin);
  val = val / 1023;
  val = val * 14;
  lcd.setCursor(0, 2);
  lcd.print("pH = ");
  lcd.print(val);

  sensorValue = analogRead(TDS_Sensor_Pin);
  Voltage = sensorValue * 5 / 1024.0;
  tdsValue = (133.42 * Voltage * Voltage * Voltage - 255.86 * Voltage * Voltage + 857.39 * Voltage) * 0.5;
  lcd.setCursor(0, 3);
  lcd.print("TDS Value = ");
  lcd.print(tdsValue);
  lcd.println(" ppm");
  delay(1000);
  //delay(10);

  if (val >= 6.5 && val <= 7.5 &&  tdsValue >= 0 && tdsValue <= 600 )
  {

    digitalWrite(ledpingreen, HIGH);
    //delay(1000);
    digitalWrite(ledpinred, LOW);
    delay(1000);

  }

  else
  {

    digitalWrite(ledpingreen, LOW);
    //delay(1000);
    digitalWrite(ledpinred, HIGH);
    //delay(1000);

  }

  /*else if (val < 6.3)
    {

    digitalWrite(ledpinred, HIGH);
    //delay(1000);
    digitalWrite(ledpinblue, LOW);
    delay(1000);
    digitalWrite(ledpingreen, LOW);
    delay(1000);*/

}

/*sensorValue = analogRead(TDS_Sensor_Pin);
  Voltage = sensorValue * 5 / 1024.0;
  tdsValue = (133.42 * Voltage * Voltage * Voltage - 255.86 * Voltage * Voltage + 857.39 * Voltage) * 0.5;
  lcd.setCursor(0, 3);
  lcd.print("TDS Value = ");
  lcd.print(tdsValue);
  lcd.println(" ppm");
  delay(100);*/
