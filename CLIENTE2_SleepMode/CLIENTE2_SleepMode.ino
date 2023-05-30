//Programa: ESP-NOW com ESP8266 NodeMCU - Emissor
//Autor: GregMaster

#include <ESP8266WiFi.h>
#include <espnow.h>

//Mac Address do NodeMCU receptor
uint8_t broadcastAddress[] = {0x4c, 0x75, 0x25, 0x36, 0xA8, 0x48};

//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct struct_message
{
  String a;
  String b;
} struct_message;

//Definicoes botao
#define pino_botao 4
int valor;
int controle_mudanca;
String banheiro = "M"; //Fem ou Masc
void ICACHE_RAM_ATTR interrupcao();
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

void ICACHE_RAM_ATTR  interrupcao() { //função de Interrupção armazenada na RAM
  valor = digitalRead(pino_botao);
  //delay(200);
  int aux_valor = digitalRead(pino_botao);

  if (valor == aux_valor) {
    if (valor == 1)
    {
      Serial.println("Ocupado");
      myData.a = "ocupado";
    } else {
      Serial.println("Livre");
      myData.a = "livre";
    }
    myData.b = banheiro;
    
    //Envia a mensagem usando o ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
}

void setup()
{
  Serial.begin(115200);
  //Coloca o dispositivo no modo Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  //Inicializa o pino do botao
  pinMode(pino_botao, INPUT_PULLUP);
  Serial.println(digitalRead(pino_botao));

  //Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  //Registra o destinatario da mensagem
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  attachInterrupt(digitalPinToInterrupt(pino_botao), interrupcao, CHANGE);
}

void loop()
{
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  delay(1);
  //ESP.deepSleep(30e6);
  //ESP.deepSleep(0);
}
