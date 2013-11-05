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
const int PROTOCOL_DATA     = 3;
const int PROTOCOL_ORIGIN   = 4;

const int RAW_IR = 11;

const int idDHT11pin = 2; //Digital pin for comunications
const int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

SoftwareSerial serial(RX_PIN,TX_PIN);

IRsend irsend;

void dht11_wrapper(); // must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);// Lib instantiate

String buffer;
void setup(){
  String comandos[6];
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
}
/*Interpretador de comandos*/
void interpreter(){
  String comandos[6];
  split(comandos,buffer,BYTE_SEPARATOR);
  if(NODE == comandos[PROTOCOL_ADRESSES].toInt()){

    int hardware = comandos[PROTOCOL_HARDWARE].toInt();
    int node = comandos[PROTOCOL_ORIGIN].toInt();

    switch(comandos[PROTOCOL_TYPE].toInt()){
    case ACTION_READ:
      comandRead(hardware,node);
      break; 
    case ACTION_WRITE:
      comandWrite(hardware,comandos[PROTOCOL_DATA],node);
      break;
    case ACTION_RESPONSE:
      comandResponse();
      break;
    }
  }  
}
void comandRead(int hardware,int node){
  switch(hardware){
  case HARDWARE_WEATHER:
      String comand = ""+node+
        BYTE_SEPARATOR+ACTION_RESPONSE+
        BYTE_SEPARATOR+HARDWARE_WEATHER+
        BYTE_SEPARATOR+DHT11.acquireAndWait()+
        DATA_SEPARATOR+char(DHT11.getHumidity())+
        DATA_SEPARATOR+char(DHT11.getCelsius())+
        BYTE_SEPARATOR+NODE;
        sendComand(comand);
    break; 
  }
}

void comandWrite(int hardware,String data,int node){
  String dataSplit[6];
  split(dataSplit,data,DATA_SEPARATOR);
  switch(hardware){
    case HARDWARE_IR:
      sendIR(dataSplit[0].toInt(),dataSplit[0]);
      break; 
    case HARDWARE_RELE:
  
      break;
  }
}
/*Metedo que escreve no sensor de infraread*/
void sendIR(int type, String data){
  long value = data.toInt();
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
  else if (type == RAW_IR) {
    int index = 0;//indice de controle dos comandos
    unsigned int raws[250];
    String s = "";
    for(int i = 0; i< data.length(); i++){
      if(data[i] == ','){//verifica se for o caracter de divisão
        raws[index] = s.toInt();
        index++;//incremente o indice para armazenar o comando em outra posição
        s="";
      }
      else{
        s.concat(data[i]);//adiciona ao indice os caracteres do comando
      }
    }    
    irsend.sendRaw(raws, 250, 38);
  }
}

void comandResponse(){
}

/*Split para string*/
void split(String comandos[6],String comando,char charSplit){  
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
void comandSucefullResponse(){

}
void comandNotFaliedResponse(){

}
//Enviar um comando
void sendComand(String comand){
  digitalWrite(DE_PIN,HIGH);//definir o pino para alto, para enviar dados
  comand = BYTE_START+comand+BYTE_STOP;
  char c[comand.length()];
  comand.toCharArray(c,comand.length()); 
  serial.write(c);//enviar o comando pela serial
  digitalWrite(DE_PIN,LOW);//finalizar o envio dos dados baixando o pino de transmissão
}




