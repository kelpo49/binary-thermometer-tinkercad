const int sensor = A0; //pino analogico do sensor que não muda
float temperaturaf = 0; //guardar variavel temperatura
int leitura = 0; //guardar variavel leitura
const int led[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; //guardar um array de 10 variaveis definidas, que não mudam
void setup() {
  Serial.begin(9600); //tempo de leitura consistente
  for(int i = 0; i < 10; i++) { //para o array com 10 elementos de 0 ate 9 = i
    pinMode(led[i],OUTPUT); //definir os leds i para output
  }
}
void loop() {
  int bit[10]; //guardar array de 10 variaveis não definidas
  leitura = analogRead(sensor); //variavel leitura oq ler do pino do sensor
  temperaturaf = leitura * 0.4887585 - 50; //conversão tensão para temperatura(formula fisica)
  int temperatura = round(temperaturaf); //arredondar para a conversão em binario dar certo(precisam ser naturais)
  for(int n = 0; n < 9; n++) { //para os bits do array de 0 até 8
    bit[n] = (abs(temperatura) >> n) & 1; //(temperatura / 2^n) mod 2
  }
  bit[9] = (temperatura < 0) ? 1: 0; //bit 9 sera 1 se temperatura for negativa
  for(int i = 0; i < 10; i++) { //para os espaços de 0 a 9 dos arrays
    digitalWrite(led[i],bit[i] == 1 ? HIGH: LOW); //associar cada led para cada bit respectivamente, se for igual 1 será high, se não, low
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