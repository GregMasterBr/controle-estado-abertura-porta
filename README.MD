# Controle de abertura/fechamento de porta.

Esse projeto é uma solução para averiguar-se se um espaço, controlado por porta, está em uso ou não. A solução foi projetada para a leitura das portas de banheiro (aberta ou fechada) de um escritório. 

Dentro deste repositório, você encontrará variações, como por exemplo:
- Código adaptado para controlar apenas um banheiro (misto);
- Código adaptado para controlar mais de um banheiro (masculino e feminino);

A solução foi desenvolvida usando placas ESP8266, tanto para o servidor, quanto para os clientes.

Os clientes, controlam o REED SWITCH, instalados na porta, e o servidor exibe a mudança de estado de cada um dos clientes. O protocolo de comunicação utilizado foi o ESP.NOW


Na pasta **teste de comunicação do protocolo ESP.NOW** você encontrará 2 versões, a primeira que envia para o servidor números aleatórios e a segunda que faz a leitura de um sensor conectado.

No código reservado ao cliente, precisa estar congfigurado o endereço MAC do ESP servidor. Por isso se faz necessário executar o código **MostraEndereçoMAC_ESP**. Execute no ESP do servidor e descubra o seu endereço MAC. No código dos clientes, você informa o endereço MAC do servidor (receptor).  

A pasta **Servidor e Cliente** executa uma rotina de comunicação 1 para 1.  

A pasta **Servidor2 e Cliente2** executa uma rotina de comunicação 1 para N.  

## Esquemático/Montagem


## Evoluções:
- Controle da carga da bateria no cliente;
- Implementar o deep sleep para economia da bateria nos clientes;


## Referências
- <https://www.arduinoecia.com.br/esp-now-comunicacao-direta-entre-modulos-esp8266-e-esp32/>  
- <https://randomnerdtutorials.com/esp-now-many-to-one-esp32/>  
- <https://blog.eletrogate.com/economizando-energia-sleep-modes-no-esp8266/>  
- <https://blog.eletrogate.com/economizando-energia-sleep-modes-no-esp8266/>  
- [SleepMode - Light Sleep](https://www.espressif.com/sites/default/files/9b-esp8266-low_power_solutions_en_0.pdf)  






