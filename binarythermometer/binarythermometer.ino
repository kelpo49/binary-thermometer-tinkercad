//by: kelpo49
//for: binary led thermometer
//date: june 9th 2025
//license: MIT
const int sensor = A0; //analog pin from sensor that doesnt change
float temperaturaf = 0; //store temperature variable
int leitura = 0; //store reading variable
const int led[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; //store an array of 10 defined variables, that dont change
void setup() {
  Serial.begin(9600); //consistent reading time
  for(int i = 0; i < 10; i++) { //for the array of 10 elements from 0 to 9 = i
    pinMode(led[i],OUTPUT); //define the i leds to output
  }
}
void loop() {
  int bit[10]; //store array of 10 undefined variables
  leitura = analogRead(sensor); //reading variable will be what it reads from the sensor pin
  temperaturaf = leitura * 0.4887585 - 50; //conversion tension to temperatura(physics equation)
  int temperatura = round(temperaturaf); //round so the conversion to binary works(they have to be from the naturals set)
  for(int n = 0; n < 9; n++) { //for the bits from the array from 0 to 8
    bit[n] = (abs(temperatura) >> n) & 1; //(temperature / 2^n) mod 2
  }
  bit[9] = (temperatura < 0) ? 1: 0; //bit 9 will be 1 if the temperature is negative
  for(int i = 0; i < 10; i++) { //for the spaces from 0 to 9 from the arrays
    digitalWrite(led[i],bit[i] == 1 ? HIGH: LOW); //associate each led to each bit respectivel, if 1 high, if not low
  }
  Serial.print("Temperatura: ");
  Serial.print(abs(temperatura));
  Serial.print(" C, Binario: ");
  for(int n = 9; n >= 0; n--) {
    Serial.print(bit[n]);
  }
  Serial.print(" , Sinal: ");
  Serial.println(bit[9] == 1 ? "(-)": "(+)");
  delay(500);
}