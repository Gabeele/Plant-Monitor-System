#include <dht.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int greenPin = A0;

#define soilSen A4
dht sensor;

#define waterLevelSig A2

void setup()
{


  Serial.begin(9600);
  lcd.begin(16, 2); //16 by 2 character display

  digitalWrite(13, OUTPUT); //init the Humidity LED
  digitalWrite(6, OUTPUT); //init the water level LED
  digitalWrite(7, OUTPUT); //init the soil level LED
  
  pinMode(10, OUTPUT);




  delay(1000);

}

void loop()
{

  sensor.read11(greenPin);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity = ");
  lcd.print(sensor.humidity);
  lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(sensor.temperature);
  delay(1000); //wait a sec (recommended for DHT11)

  int humMax = 55;

  if ((sensor.humidity) > humMax) {
    digitalWrite(8, HIGH);

  }
  else {

    digitalWrite(8, LOW);
  }

  delay(3000); //wait a sec (recommended for DHT11


  int waterLevelValue = analogRead(waterLevelSig);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water = ");

  if (waterLevelValue > 100) {
    digitalWrite(6, HIGH);
    lcd.print("Ok");

  } else {
    digitalWrite(6, LOW);
    lcd.print("Low");
  }


  const int drySoil = 606;
  const int wetSoil = 284;

  int soilSenValue = analogRead(soilSen);

  Serial.print(soilSenValue);
  Serial.print("\n");

  int perSoilSen = map(soilSenValue, wetSoil, drySoil, 100, 0);

  lcd.setCursor(0, 1);
  lcd.print("Soil = ");
  lcd.print(perSoilSen);
  lcd.print("%");

  while (perSoilSen < 10) {
    digitalWrite(7, HIGH);
    digitalWrite(10, HIGH);
    int soilSenValue = analogRead(soilSen);
    int perSoilSen = map(soilSenValue, wetSoil, drySoil, 100, 0);
  
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("     ALERT!     ");
    lcd.setCursor(0, 1);
    lcd.print("Soil = ");
    lcd.print(perSoilSen);
    lcd.print("%");


    if (perSoilSen > 80) {
      digitalWrite(7, LOW);
      digitalWrite(10, LOW);
      break;
    }

    delay(500);


  }

  delay(3000); //wait a sec (recommended for DHT11)


}
