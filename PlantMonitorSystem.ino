//Includes
#include <LiquidCrystal.h>



//Conestant pins

const int SOIL_SEN = A0;  //Capacitive soil moisture sensor
const int WATER_PUMP = 2; //Water pump

//LCD Display pins and configure
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//constants varaibles
const int dry_map = 606;      // value for dry sensor to map
const int wet_map = 284;      // value for wet sensor to map
const int dry = 0;            // value for dry sensor
const int wet = 100;          // value for wet sensor
const int dry_check_val = 10; // Percentage to check wheather the soil is dry

void setup()
{

  Serial.begin(9600);
  pinMode(WATER_PUMP, OUTPUT);
}

void loop()
{

  maintainSoil();

  // delay(1200000);
  delay(1000);
}

//Obtains the soil moisture as a percentage
int getSoilMoisture()
{

  int soil_sen_value = analogRead(SOIL_SEN);
  int percentageHumididy = map(soil_sen_value, wet_map, dry_map, wet, dry);

  return percentageHumididy;
}

//Obtains if the soil is dry or not according to the threshold
//soil_moist -> Percentage of moistuire
bool getSoilStatus(int soil_moist)
{

  if (soil_moist <= dry_check_val)
  {
    return true;
  }
  else if (soil_moist > dry_check_val)
  {
    return false;
  }
  else
  {
    return false;
  }
}

//Turns the water pump off
void turnPumpOff()
{
  digitalWrite(WATER_PUMP, LOW);
}

//Turns the water pump on
void turnPumpOn()
{
  digitalWrite(WATER_PUMP, HIGH);
}

//Displays a percentages to the serial
void displayAsPercentage(int value)
{

  Serial.print(value);
  Serial.println("%");
}

//Parent function to check soil and water if necessary
void maintainSoil()
{

    int soil_moist;
    bool isDry;

  do
  {
    soil_moist = getSoilMoisture();
    isDry = getSoilStatus(soil_moist);

    displayAsPercentage(soil_moist);
    if (isDry)
    {
      turnPumpOn();
    }
    else
    {
      turnPumpOff();
    }

  } while (getSoilStatus(soil_moist));

}
