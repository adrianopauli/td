#include <IRremote.h>
#include <SoftwareSerial.h>
#include <idDHT11.h>

const int RX_PIN = 10;
const int TX_PIN = 11;
const int RE_PIN = 4;
const int DE_PIN = 5;
const int NODE = 2;

const char BYTE_START  = '#';
const char BYTE_STOP   = '$';
const char BYTE_SEPARATOR  = '/';
const char DATA_SEPARATOR  = '?';

const int ACTION_READ     = 1;
const int ACTION_WRITE    = 2;
const int ACTION_RESPONSE = 3;

const int HARDWARE_IR       = 91;
const int HARDWARE_RELE     = 92;
const int HARDWARE_WEATHER  = 93;

const int PROTOCOL_ADRESSES = 0;
const int PROTOCOL_TYPE     = 1;
const int PROTOCOL_HARDWARE = 2;
const int PROTOCOL_NODE_ORIGIN   = 3;
const int PROTOCOL_DATA     = 4;

const String DATA_ERROR = "ERROR";
const int RAW_IR = 11;

const int idDHT11pin = 2; //Digital pin for comunications
const int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

SoftwareSerial serial(RX_PIN,TX_PIN);

IRsend irsend;

void dht11_wrapper(); // must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);// Lib instantiate

String buffer = "";
void setup(){
  Serial.begin(9600);
  serial.begin(4800);

  pinMode(RE_PIN,OUTPUT);
  pinMode(DE_PIN,OUTPUT);
  digitalWrite(RE_PIN,LOW);
  digitalWrite(DE_PIN,LOW);
}

void dht11_wrapper() {
  DHT11.isrCallback();
}

void loop(){
  ler();
}
/*Metodo que lê os dados e destina para o interpretador os comandos obtidos*/
void ler(){
  if(serial.available()){//Serial disponivel
    char c = serial.read();
    if(c == BYTE_START ){//se o byte for o inicial
      buffer = "";//zera o buffer
    }
    else if(c == BYTE_STOP){// se o byte for o final
      interpreter();//chamada do metodo para interpretar o comando armazenado no buffer
    }
    else{      
      buffer.concat(c);//leitura dos dados para o buffer
    }
  }
}/*Interpretador de comandos*/
void interpreter(){
  String comandos[7];  
  split(comandos,buffer,BYTE_SEPARATOR);//realizar os splits dos comandos
  if(NODE == comandos[PROTOCOL_ADRESSES].toInt()){//verifica se o camando é pro nó

    int hardware = comandos[PROTOCOL_HARDWARE].toInt();//pega o hardware
    int node = comandos[PROTOCOL_NODE_ORIGIN].toInt();//pega o numero do nó de origem

    switch(comandos[PROTOCOL_TYPE].toInt()){
    case ACTION_READ://é leitura
      comandRead(hardware,node);
      break; 
    case ACTION_WRITE://é estrita
      comandWrite(hardware,comandos[PROTOCOL_DATA],node);
      break;
    case ACTION_RESPONSE://é uma resposta

      break;
    }
  } 
}
void comandRead(int hardware,int node){
  switch(hardware){
  case HARDWARE_WEATHER:
    weather(node);
    break; 
  }
}
void weather(int node){
  int result = DHT11.acquireAndWait();
  if(IDDHTLIB_OK == result){ 
    String data;
    char buffer[10];
    dtostrf(DHT11.getHumidity(), 2, 1, buffer);
    data.concat(buffer);
    data.concat(DATA_SEPARATOR);
    dtostrf(DHT11.getCelsius(), 2, 1, buffer);
    data.concat(buffer);
    sendComand(node,ACTION_RESPONSE,HARDWARE_WEATHER,data);
  }
  else{
    sendComand(node,ACTION_RESPONSE,HARDWARE_WEATHER,DATA_ERROR);  
  }
}
void comandWrite(int hardware,String data,int node){
  switch(hardware){
    case HARDWARE_IR:
      sendIR(data);
      break; 
    case HARDWARE_RELE:
  
      break;
  }
}
/*Metedo que escreve no sensor de infraread*/
void sendIR(String data){
  String dataSplit[7];
  split(dataSplit,data,DATA_SEPARATOR);
  int type = dataSplit[0].toInt();
  if (type == RAW_IR) {   
    Serial.print("Chamou");  
    decondIR(dataSplit);
  }
  else {
    long value = dataSplit[1].toInt();
    if (type == NEC) {
      irsend.sendNEC(value, 32);
    } 
    else if (type == SONY) {
      irsend.sendSony(value, 12);
    } 
    else if (type == RC5) {
      irsend.sendRC5(value, 11);
    } 
    else if (type == RC6) {
      irsend.sendRC6(value, 1);
    }
    else if (type == PANASONIC) {
      irsend.sendPanasonic(value, 48);
    } 
    else if (type == JVC) {
      irsend.sendJVC(value, 16,1);
    } 
  }
}

/*Split para string*/
void split(String comandos[7],String comando,char charSplit){  
  int index = 0;//indice de controle dos comandos
  for(int i = 0; i< comando.length(); i++){
    if(comando[i] == charSplit){//verifica se for o caracter de divisão
      index++;//incremente o indice para armazenar o comando em outra posição
    }
    else{
      comandos[index].concat(comando[i]);//adiciona ao indice os caracteres do comando
    }
  }
}
//Enviar um comando
void sendComand(int node,int action,int hardware,String data){  
  String comand;
  comand.concat(BYTE_START);
  comand.concat(node);
  comand.concat(BYTE_SEPARATOR);
  comand.concat(action);
  comand.concat(BYTE_SEPARATOR);
  comand.concat(hardware);
  comand.concat(BYTE_SEPARATOR);
  comand.concat(NODE);
  comand.concat(BYTE_SEPARATOR);
  comand.concat(data);  
  comand.concat(BYTE_STOP);

  char c[comand.length()+1];
  comand.toCharArray(c,comand.length()+1); 
  digitalWrite(DE_PIN,HIGH);//definir o pino para alto, para enviar dados
  serial.write(c);//enviar o comando pela serial
  digitalWrite(DE_PIN,LOW);//finalizar o envio dos dados baixando o pino de transmissão
}

void decondIR(String comandos[7]){
  int maior = comandos[4].toInt();
  int menor = comandos[5].toInt();
  unsigned int raw[228] = {comandos[1].toInt(),comandos[2].toInt(),comandos[3].toInt()};
  int cont = 3;
  Serial.print(comandos[6]);
  for(int i =0;i < comandos[6].length();i++){
    int number = 0;
    char c = comandos[6][i];
    if(c == 'f' || c == 'F'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == 'e' || c == 'E'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
  }else if(c == 'd' || c == 'D'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
  }else if(c == 'c' || c == 'C'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
  }else if(c == 'b' || c == 'B'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
  }else if(c == 'a' || c == 'A'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '9'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '8'){
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '7'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '6'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '5'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '4'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '3'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '2'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '1'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = maior;
      cont++;
      raw[cont] = menor;
      cont++;
    }else if(c == '0'){
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
      raw[cont] = menor;
      cont++;
    }
  }
  irsend.sendRaw(raw, 228, 38);
}
