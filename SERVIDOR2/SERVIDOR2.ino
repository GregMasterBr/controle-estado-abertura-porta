//Programa: ESP-NOW com ESP8266 NodeMCU - Receptor
//Autor: GregMaster

#include <ESP8266WiFi.h>
#include <espnow.h>

//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct struct_message
{
  String a;
  String b;
} struct_message;

//Definicoes led
#define pino_led_verde_M 5
#define pino_led_vermelho_M 2

#define pino_led_verde_F 13
#define pino_led_vermelho_F 14

//Cria uma struct_message chamada myData
struct_message myData;

//Funcao de Callback executada quando a mensagem for recebida
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)
{
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println();
  Serial.print("Bytes recebidos: ");
  Serial.println(len);  Serial.print("String: ");
  Serial.println(myData.a);
  Serial.print("String: ");
  Serial.println(myData.b);
  String dado_recebido = myData.a;
  String qual_banheiro = myData.b;
  //Acende ou apaga o led de acordo com a String recebida
  if (dado_recebido == "ocupado")
  {
    Serial.println("Banheiro OCUPADO!");
    ocupado(qual_banheiro);
  }

  if (dado_recebido == "livre")
  {
    Serial.println("Banheiro LIVRE!");
    livre(qual_banheiro);
  }
}

void ocupado(String banheiro) {
  if (banheiro=="F"){
    digitalWrite(pino_led_verde_F, LOW);
    digitalWrite(pino_led_vermelho_F, HIGH);    
  }
  if (banheiro=="M"){
    digitalWrite(pino_led_verde_M, LOW);
    digitalWrite(pino_led_vermelho_M, HIGH);    
  }
}

void livre(String banheiro) {
  if (banheiro=="F"){
    digitalWrite(pino_led_verde_F, HIGH);
    digitalWrite(pino_led_vermelho_F, LOW);    
  }
  if (banheiro=="M"){
    digitalWrite(pino_led_verde_M, HIGH);
    digitalWrite(pino_led_vermelho_M, LOW);    
  }  
}


void setup()
{
  Serial.begin(115200);

  pinMode(pino_led_verde_M, OUTPUT);
  digitalWrite(pino_led_verde_M, LOW);
  pinMode(pino_led_vermelho_M, OUTPUT);
  digitalWrite(pino_led_vermelho_M, LOW);

  pinMode(pino_led_verde_F, OUTPUT);
  digitalWrite(pino_led_verde_F, LOW);
  pinMode(pino_led_vermelho_F, OUTPUT);
  digitalWrite(pino_led_vermelho_F, LOW);

  //Coloca o dispositivo no modo Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  //Neste programa nao temos comandos no loop
}
