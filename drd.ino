///Variáveis Método LDR
#define sensorLDR1 A2 //LDR DIREITA
int val1 = 0;
int valRef1 = 0;
#define sensorLDR2 A3 //LDR ESQUERDA
int val2 = 0;
int valRef2 = 0;

//Varíavel Método Temperatura
#define LM35 A0

//Variáveis Método Transmissão
unsigned long tempo = 0;
unsigned long tempodelay = 10;


//Variáveis Metodo Movimento
#define direcao_Dianteiro 7 
#define velocidade_Dianteiro 6
#define direcao_Traseiro 8 
#define velocidade_Traseiro 9
#define direcao_equador 4
#define velocidade_equador 5
#define direcao_meridiano 12
#define velocidade_meridiano 10
unsigned long tempoMotor = 0;
unsigned long tempoMotorDelay = 100;
unsigned long tempoMotorDelay2 = 1000;

///Variáveis Método Receptor
int DD = 0; 
int VD = 0;
int DT = 0; 
int VT = 0;

//Variáveis de Indicador de giro
#define botaoMeridiano 13     
int valorMeridiano = 1;
#define botaoDianteiro 3
int valorDianteiro = 1;
#define botaoEquador 2
int valorEquador = 1;
#define sensorTraseiro A1
int valorTraseiroInicial = 0;
int valorTraseiroFinal = 0;
bool movimento = false;
 
void setup() {
  //Comunicação Serial
  Serial.begin(9600); // abre a porta serial, configura a taxa de transferência para 9600 bps

  //Para Movimento
  pinMode(direcao_Dianteiro, OUTPUT);
  pinMode(velocidade_Dianteiro, OUTPUT);
  pinMode(direcao_Traseiro, OUTPUT);
  pinMode(velocidade_Traseiro, OUTPUT);
  pinMode(direcao_equador, OUTPUT);
  pinMode(velocidade_equador, OUTPUT);
  pinMode(direcao_meridiano, OUTPUT);
  pinMode(velocidade_meridiano, OUTPUT);

  //Para Indicador de giro
  pinMode(botaoMeridiano, INPUT_PULLUP);
  pinMode(botaoDianteiro, INPUT_PULLUP);
  pinMode(botaoEquador, INPUT_PULLUP);


}//fim setup

void loop() {

  receptor();
  
  transmissaoDados();

}//fim de loop

void receptor(){
    int direcDiant;
    int velocDiant;
    int direcEquad;
    int velocEquad;
    int direcMerid;
    int velocMerid;
    int direcTras;
    int velocTras;
   if(Serial.available()>0){
    direcDiant = Serial.readStringUntil('!').toInt();
    velocDiant = Serial.readStringUntil('@').toInt();
    direcEquad = Serial.readStringUntil('#').toInt();
    velocEquad = Serial.readStringUntil('$').toInt();
    direcMerid = Serial.readStringUntil('%').toInt();
    velocMerid = Serial.readStringUntil('&').toInt();
    direcTras = Serial.readStringUntil('?').toInt();
    velocTras = Serial.readStringUntil('\n').toInt();  
    }
    motorDianteiro (direcDiant, velocDiant);
    motorEquador (direcEquad, velocEquad);
    motorMeridiano (direcMerid, velocMerid);
    motorTraseiro (direcTras, velocTras);
     
  }//fim de receptor
  
void transmissaoDados(){
  tempo = millis();
  while((millis() - tempo)<tempodelay){
    if ((millis() - tempo)>tempodelay){
        Serial.print(LDR1());
        Serial.print(";");
        Serial.print(LDR2());
        Serial.println("!");
        }
      }  
}// fim de transmissaoDados

float temperaturaL293D () {
  float temperatura = (float(analogRead(LM35))*5/(1023))/0.023;
  return temperatura;
  
}//fim de temperaturaL293D

int LDR1 (){
    val1 = analogRead(sensorLDR1);
       if(val1!=valRef1 && val1!=(valRef1+1) && val1!=(valRef1-1) && val1!=(valRef1+2) && val1!=(valRef1-2)){
            valRef1 = val1;
       }//fim de if
    return valRef1;
}//fim de LDR1

int LDR2 (){
    val2 = analogRead(sensorLDR2);
      if(val2!=valRef2 && val2!=(valRef2+1) && val2!=(valRef2-1) && val2!=(valRef2+2) && val2!=(valRef2-2)){
            valRef2 = val2;
      }//fim de if
    return valRef2;
}//fim de LDR2

void motorDianteiro ( int direcao, int velocidade){
  valorDianteiro = digitalRead(botaoDianteiro);
  if(temperaturaL293D () > 85){
    analogWrite(velocidade_Dianteiro, 0);
  }else if (valorDianteiro = 1){ //quando o valor for zero o botao esta pressionado
    digitalWrite(direcao_Dianteiro, direcao);
    analogWrite(velocidade_Dianteiro, velocidade);
  }else {
    analogWrite(velocidade_Dianteiro, 0);
  }
}//fim de motorDianteiro

void motorEquador ( int direcao, int velocidade){
  valorEquador = digitalRead(botaoEquador);
  if (valorEquador = 1){
    digitalWrite(direcao_equador, direcao);
    analogWrite(velocidade_equador, velocidade);
  }else {
    analogWrite(velocidade_equador, 0);
  }
}//fim de motorEquador

void motorMeridiano ( int direcao, int velocidade){
  valorMeridiano = digitalRead(botaoMeridiano);
  if (valorMeridiano = 1){
    digitalWrite(direcao_meridiano, direcao);
    analogWrite(velocidade_meridiano, velocidade);
  }else {
    analogWrite(velocidade_meridiano, 0);
  }
}//fim de motorMeridiano

void motorTraseiro (int direcao, int velocidade){
    digitalWrite(direcao_Traseiro, direcao);
    analogWrite(velocidade_Traseiro, velocidade);
    
  tempoMotor = millis();
  while((millis() - tempoMotor)<tempoMotorDelay){
    if ((millis() - tempoMotor)>tempoMotorDelay){
        valorTraseiroInicial = analogRead(sensorTraseiro);
        }
      }//fim de while
      
  while((millis() - tempoMotor)<tempoMotorDelay){
    if ((millis() - tempoMotor)>tempoMotorDelay){
        valorTraseiroFinal = analogRead(sensorTraseiro);
        }
      }//fim de while
        
  if ((valorTraseiroInicial < 60 && valorTraseiroFinal > 100) || (valorTraseiroInicial > 100 && valorTraseiroFinal < 60)){
    movimento = true;
  }
  
    while((millis() - tempoMotor)<tempoMotorDelay2){
    if ((millis() - tempoMotor)>tempoMotorDelay2){
        valorTraseiroFinal = analogRead(sensorTraseiro);
        }
      }//fim de while
      
  if ((valorTraseiroInicial < 60 || valorTraseiroFinal < 60) || (valorTraseiroInicial > 100 || valorTraseiroFinal > 100) || (temperaturaL293D () > 85)){
    movimento = false;
    analogWrite(velocidade_Traseiro, 0);
  }
}//fim de motorTraseiro
