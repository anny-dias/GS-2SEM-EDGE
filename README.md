# GLOBAL SOLUTION - EDGE COMPUTING & COMPUTER SYSTEMS
# OTIMIZAÇÃO DO USO DE MEDICAMENTOS: ESTRATÉGIAS TECNOLÓGICAS PARA MINIMIZAR O DESPERDÍCIO E APRIMORAR A GESTÃO

- Anny Carolina: 98295-1ESPH 


## Introdução

  O desperdício de medicamentos é uma questão complexa e preocupante que afeta não apenas o setor da saúde, mas também tem impactos ambientais e econômicos significativos. Este fenômeno ocorre em diferentes estágios da cadeia de suprimentos farmacêuticos, desde a produção até o consumo final pelos pacientes. O desperdício pode se manifestar de várias maneiras, como a expiração de medicamentos, descarte inadequado, armazenamento inadequado, interrupção do tratamento antes do término do medicamento e distribuição ineficiente.
O aumento do desperdício de medicamentos não apenas representa uma perda de recursos valiosos, mas também levanta questões éticas e sociais. Em muitas partes do mundo, enquanto algumas pessoas têm dificuldades em acessar medicamentos essenciais, outros medicamentos são descartados sem serem utilizados, contribuindo para disparidades no acesso à saúde.
Além disso, o impacto ambiental do desperdício de medicamentos não pode ser subestimado. A produção e descarte inadequados de medicamentos podem resultar em poluição da água e do solo, representando uma ameaça para os ecossistemas e a vida selvagem. Isso levanta a necessidade urgente de abordar não apenas as práticas de gestão de fármacos, mas também de repensar os sistemas de saúde e distribuição de medicamentos.
Neste trabalho, exploraremos as principais causas do desperdício de medicamentos, os impactos negativos associados a essa prática e as possíveis soluções tecnológicas e estratégias para minimizar esse problema crescente. O entendimento e a conscientização sobre esse desperdício são fundamentais para desenvolver abordagens eficazes e sustentáveis que garantam o acesso equitativo aos medicamentos necessários, enquanto reduzem o impacto ambiental e otimizam os recursos disponíveis no campo da saúde.

## Solução

  A tecnologia desempenha um papel crucial no combate ao desperdício de medicamentos em vários níveis, desde a produção até o consumo final. Desse modo, o sistema de monitoramento de temperatura e umidade é uma solução tecnológica que busca minimizar essa problemática e aprimorar sua gestão. Esse sistema consiste em utilizar sensores de temperatura e umidade conectados ao ESP32 para monitorar as condições ambientais onde os medicamentos estão armazenados. Configurando alertas para notificar quando as condições ultrapassam limites seguros para armazenamento.


## Instruções de como configurar e executar a aplicação
###  Materiais necessários:
<ul>
  <li>ESP32</li>
  <li>Sensor de temperatura e umidade DHT22</li>
  <li>Cabos de conexão</li>
  <li>Resistor</li>
  <li>Placa de ensaio</li>
</ul>

### Passos: 

#### 1- Instalar Bibliotecas:
<ul>
    <li>Abra o Arduino IDE.</li>
    <li>Vá em "Sketch" -> "Incluir Biblioteca" -> "Gerenciar Bibliotecas".</li>
    <li>Pesquise e instale as seguintes bibliotecas: "DHT sensor library" (para o sensor DHT22) e "PubSubClient" (para comunicar com MQTT)</li>
</ul>

#### 2- Conectar Hardware:
<ul>
    <li>Conecte o DHT22 ao ESP32 usando fios. Conecte o pino de dados do DHT22 a um pino digital (D2) no ESP32.</li>
    <li>Certifique-se de alimentar o DHT22 com a voltagem correta</li>
</ul>

#### 3- Programar o ESP32:
<ul>
    <li>Abra o Arduino IDE e crie um novo sketch.</li>
    <li>Inclua as bibliotecas necessárias no início do código.</li>
</ul>

      ```
        #include "DHT.h"
        #include <PubSubClient.h> 
        #include <WiFi.h>
      ```
<ul>
    <li>Definindo Topicos</li>
</ul>

    ```
        #define TOPICO_SUBSCRIBE    "/TEF/lamp105/cmd"        //Tópico MQTT de escuta
        #define TOPICO_PUBLISH      "/TEF/lamp105/attrs"      //Tópico MQTT de envio de informações para Broker
        #define TOPICO_PUBLISH_3    "/TEF/lamp105/attrs/u"    //Tópico MQTT dos dados de Umidade
        #define TOPICO_PUBLISH_4    "/TEF/lamp105/attrs/t"    //Tópico MQTT dos dados de Temperatura
        #define ID_MQTT  "fiware_109"   //id mqtt (para identificação de sessão)

      ```

<ul>
    <li>WIFI</li>
</ul>

    ```
        const char* SSID = "Wokwi-GUEST"; // SSID / nome da rede WI-FI 
        const char* PASSWORD = ""; // Senha da rede WI-FI
          
        // MQTT
        const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
        int BROKER_PORT = 1883;                    // Porta do Broker MQTT
        
        // Variáveis e objetos globais
        WiFiClient espClient;          // Cria o objeto espClient
        PubSubClient MQTT(espClient);  // Instancia o Cliente MQTT passando o objeto espClient
        char EstadoSaida = '0';        // Variável que armazena o estado atual da saída
      ```
<ul>
    <li>Prototypes</li>
</ul>

      ```
        void initSerial();
        void initWiFi();
        void initMQTT();
        void reconectWiFi(); 
        void mqtt_callback(char* topic, byte* payload, unsigned int length);
        void VerificaConexoesWiFIEMQTT(void);
        void InitOutput(void);


      ```
<ul>
    <li>DHT22</li>
</ul>

      ```
        #define DHTPIN 2
        #define DHTTYPE DHT22
        //#define DHTTYPE DHT11
        DHT dht(DHTPIN, DHTTYPE);


      ```



<ul>
    <li>Funções de inicialização</li>
</ul>
      
      ```
       void setup() {
            // put your setup code here, to run once:
            // Inicializações:
            InitOutput();
            initSerial();
            initWiFi();
            initMQTT();
            delay(5000);
          
            Serial.println(F("DHTxx Test!"));
          }
          
          void initSerial() 
          {
            Serial.begin(115200);
          }
          
          // Função: Inicializa e conecta-se na rede WI-FI desejada
          void initWiFi() 
          {
              delay(10);
              Serial.println("----- Conexão WI-FI -----");
              Serial.print("Conectando-se na rede: ");
              Serial.println(SSID);
              Serial.println("Aguarde...");
               
              reconectWiFi();
          }
            
          // Função: Inicializa parâmetros de conexão MQTT(endereço do broker, porta e seta função de callback)
          void initMQTT() 
          {
              MQTT.setServer(BROKER_MQTT, BROKER_PORT); 
              MQTT.setCallback(mqtt_callback);
          }
      ```
<ul>
    <li>Função de callback: Chamada toda vez que uma informação de um dos tópicos subescritos chega</li>
</ul>
      
      ```
                 void mqtt_callback(char* topic, byte* payload, unsigned int length) 
          {
              String msg;
              //obtem a string do payload recebido
              for(int i = 0; i < length; i++) 
              {
                 char c = (char)payload[i];
                 msg += c;
              }
              Serial.print("- Mensagem recebida: ");
              Serial.println(msg);
            
              // Toma ação dependendo da string recebida:
              // Verifica se deve colocar nivel alto de tensão na saída D0:
              if (msg.equals("lamp105@on|"))
              {
                  digitalWrite(2, HIGH);
                  EstadoSaida = '1';
              }
           
              //Verifica se deve colocar nivel alto de tensão na saída D0:
              if (msg.equals("lamp105@off|"))
              {
                  digitalWrite(2, LOW);
                  EstadoSaida = '0';
              }
              
          }
      ```
<ul>
    <li>Função: Reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair) em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.</li>
</ul>
      
      ```void reconnectMQTT() 
        {
            while (!MQTT.connected()) 
            {
                Serial.print("* Tentando se conectar ao Broker MQTT: ");
                Serial.println(BROKER_MQTT);
                if (MQTT.connect(ID_MQTT)) 
                {
                    Serial.println("Conectado com sucesso ao Broker MQTT!");
                    MQTT.subscribe(TOPICO_SUBSCRIBE); 
                } 
                else
                {
                    Serial.println("Falha ao reconectar no Broker.");
                    Serial.println("Nova tentativa de conexão em 2s");
                    delay(2000);
                }
            }
      }    
      ```
<ul>
    <li>Função: Reconecta-se ao WiFi</li>
</ul>
      
      ```void reconectWiFi() 
        {
          // Se já está conectado a rede WI-FI, nada é feito. Caso contrário, ocorrerá tentativas           de conexão
          if (WiFi.status() == WL_CONNECTED)
              return;
                
          WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
            
          while (WiFi.status() != WL_CONNECTED) 
          {
              delay(100);
              Serial.print(".");
          }
          
          Serial.println();
          Serial.print("Conectado com sucesso na rede: ");
          Serial.print(SSID);
          Serial.print("\n");
          Serial.print("IP obtido: ");
          Serial.println(WiFi.localIP());
        }
 
      ```

  <ul>
    <li>Função: Verifica o estado das conexões WiFI e ao broker MQTT. Em caso de desconexão, a conexão é refeita.</li>
</ul>
      
      ```void VerificaConexoesWiFIEMQTT(void)
        {
            if (!MQTT.connected()) 
                reconnectMQTT(); //Se não há conexão com o Broker, a conexão é refeita
             
             reconectWiFi(); //Se não há conexão com o WiFI, a conexão é refeita
        }
 
      ```

  <ul>
    <li>Função: Envia ao Broker o estado atual do output </li>
</ul>
      
      ```void EnviaEstadoOutputMQTT(void)
      {
          if (EstadoSaida == '1')
          {
            MQTT.publish(TOPICO_PUBLISH, "s|on");
            Serial.println("- Led Ligado");
          }
          if (EstadoSaida == '0')
          {
            MQTT.publish(TOPICO_PUBLISH, "s|off");
            Serial.println("- Led Desligado");
          }
          Serial.println("- Estado do LED enviado ao Broker!");
          delay(1000);
      }
      ```

  <ul>
    <li> Função: Inicializa o output em nível lógico baixo </li>
</ul>
      
      ```void InitOutput(void)
        {
            // IMPORTANTE: O Led já contido na placa é acionado com lógica invertida (ou seja,
            // enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
            pinMode(2, OUTPUT);
            digitalWrite(2, HIGH);
            
            boolean toggle = false;
        
            for(int i = 0; i <= 10; i++)
            {
                toggle = !toggle;
                digitalWrite(2,toggle);
                delay(200);           
            }
        
            digitalWrite(2, LOW);
        }

      ```
<ul>
    <li> Void loop: </li>
</ul>

      ```
      
      void loop() {
        // put your main code here, to run repeatedly:
        delay(2000);
      
        char msgBuffer[4];
        // Garante funcionamento das conexões WiFi e ao broker MQTT
        VerificaConexoesWiFIEMQTT();
      
        // Envia o status de todos os outputs para o Broker no protocolo esperado
        EnviaEstadoOutputMQTT();
      
        // keep-alive da comunicação com broker MQTT
        MQTT.loop();
      
        // Leitura DHT
        float h = dht.readHumidity();
        dtostrf(h, 4, 2, msgBuffer);
        MQTT.publish(TOPICO_PUBLISH_3,msgBuffer);
      
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);
        dtostrf(t, 4, 2, msgBuffer);
        MQTT.publish(TOPICO_PUBLISH_4,msgBuffer);
      
        if (isnan(h) || isnan(t) || isnan(f)){
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }
      
        float hif = dht.computeHeatIndex(f, h);
        float hic = dht.computeHeatIndex(t, h, false);
      
      
        Serial.print(F("Umidade:  "));
        Serial.print(h);
        Serial.print(F("% || Temperatura: "));
        Serial.print(t);
        Serial.print(F("°C "));
        Serial.print(f);
        Serial.print(F("°F || Indice de calor: "));
        Serial.print(hic);
        Serial.print(F(" °C "));
        Serial.print(hif);
        Serial.println(F(" °F "));
      
      }
      ```
                
#### 4- Upload e Monitoramento:
<ul>
    <li>Compile e faça o upload do código para o seu ESP32.</li>
</ul>

## Simulação do projeto
https://wokwi.com/projects/382308893669669889

## Link para o vídeo
aqui

## Copyright

ATENÇÃO: O programa deve ser utilizado EXCLUSIVAMENTE como forma de estudos para aqueles que baixarem sem serem as desenvolvedoras. <br>

Copyright ©️ Anny.
