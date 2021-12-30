//Includes

//Conestant pins

const int SOIL_SEN = A0;  //Capacitive soil moutiure sensor
const int WATER_PUMP = 2;  //Water pump 

  //constants varaibles
  const int dry_map = 606; // value for dry sensor to map
  const int wet_map = 284; // value for wet sensor to map
  const int dry = 0; // value for dry sensor
  const int wet = 100; // value for wet sensor
  const int dry_check_val = 15; // Percentage to check wheather the soil is dry


void setup()
{


  Serial.begin(9600);
  pinMode(WATER_PUMP, OUTPUT);


}

void loop()
{
  int soil_moist = getSoilMoisture();
  
  bool isDry = getSoilStatus(soil_moist);

  displayAsPercentage(soil_moist);

  
  if(isDry){
    //turnPumpOn();
  }else{
    //turnPumpOff();
  }
  
  delay(2000);
  
}

int getSoilMoisture(){

    int soil_sen_value = analogRead(SOIL_SEN);
    int percentageHumididy = map(soil_sen_value, wet_map, dry_map, wet, dry); 
    
  return percentageHumididy;
}

bool getSoilStatus(int soil_moist){

  if (soil_moist <= dry_check_val){
    return true;
  }
  else if (soil_moist > dry_check_val){
    return false;
  }
  else{
    return false;
  }
  
}

void turnPumpOff(){
  digitalWrite(WATER_PUMP, LOW);
}

void turnPumpOn(){
  digitalWrite(WATER_PUMP, HIGH);
}

void displayAsPercentage(int value){

  Serial.print(value);
  Serial.println("%");

}
