#include <IRremote.h>

int RECV_PIN = 12;

const int RAW_IR = 11;

const char DATA_SEPARATOR  = '&';

IRrecv irrecv(RECV_PIN);
decode_results results;

void decondificador(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    int count = results->rawlen;
    int cont = 0;
    boolean c[4];
    String comando = "";
    int maior = 0;
    int menor = 0;
    for (int i = 4; i < count; i = i+2) { 
      if(cont == 4){
        cont = 0; 
        comando.concat(String(convert(c),HEX));
      }
      int number = results->rawbuf[i]*USECPERTICK;
      if(number>1000){
        c[cont]=true;
        maior = number;
      }
      else{
        menor = number;
        c[cont]=false;
      }
      cont++;
    }
    comando.concat(String(convert(c),HEX));
    String comandos = String(RAW_IR);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(results->rawbuf[1]*USECPERTICK);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(results->rawbuf[2]*USECPERTICK);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(results->rawbuf[3]*USECPERTICK);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(maior);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(menor);
    comandos.concat(DATA_SEPARATOR);
    comandos.concat(comando);
    Serial.println(comandos);
  }
  else if (results->decode_type == NEC) {
    Serial.print(NEC);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  } 
  else if (results->decode_type == SONY) {
    Serial.print(SONY);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  } 
  else if (results->decode_type == RC5) {
    Serial.print(RC5);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  } 
  else if (results->decode_type == RC6) {
    Serial.print(RC6);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  }
  else if (results->decode_type == JVC) {
    Serial.print(JVC);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print(PANASONIC);
    Serial.print(DATA_SEPARATOR);
    Serial.print(String(results->value, DEC));
    Serial.println();
  }
  else{
    Serial.println("ERROR");
  }
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    decondificador(&results);
    irrecv.resume(); // Receive the next value
  }
}
int convert(boolean b[4]){
  int soma = 0;
  if(b[0]){
    soma += 8;
  }
  if(b[1]){
    soma += 4;
  }
  if(b[2]){
    soma += 2;
  } 
  if(b[3]){
    soma += 1;
  }
  return soma;
}






