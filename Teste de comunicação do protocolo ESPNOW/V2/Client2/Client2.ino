//Programa: ESP-NOW com ESP8266 NodeMCU - Emissor
//Autor: GregMaster

#include <ESP8266WiFi.h>
#include <espnow.h>
#define pino_botao 4

//Coloque na linha abaixo o Mac Address do NodeMCU receptor
uint8_t broadcastAddress[] = {0x4c, 0x75, 0x25, 0x36, 0xA8, 0x48};

//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct struct_message
{
  String a;
} struct_message;

int valor;

//Cria uma struct_message chamada myData
struct_message myData;

//Callback quando os dados sao enviados
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
  Serial.print("Status dos dados enviados: ");
  if (sendStatus == 0) {
    Serial.println("Envio ok!");
  }
  else {
    Serial.println("Falha no envio!");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(pino_botao, INPUT);
  Serial.println(pino_botao);
  //Coloca o dispositivo no modo Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  //Registra o destinatario da mensagem
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop()
{
  valor = digitalRead(pino_botao);
  Serial.println(digitalRead(pino_botao));
  //valor = random(99);
  Serial.print("valor: ");  
  Serial.println(valor);  
  delay(500);
  
  myData.a = String(valor);
  //Envia a mensagem usando o ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));    
}
