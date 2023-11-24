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
</ul>

### Passos: 

#### 1- Instalar Bibliotecas:
<ul>
    <li>Abra o Arduino IDE.</li>
    <li>Vá em "Sketch" -> "Incluir Biblioteca" -> "Gerenciar Bibliotecas".</li>
    <li>Pesquise e instale as seguintes bibliotecas: "DHT sensor library" (para o sensor DHT22) e "Adafruit Unified Sensor" (uma dependência para a biblioteca do DHT)</li>
</ul>

#### 2- Conectar Hardware:
<ul>
    <li>Conecte o DHT22 ao ESP32 usando fios. Conecte o pino de dados do DHT22 a um pino digital (D1) no ESP32.</li>
    <li>Certifique-se de alimentar o DHT22 com a voltagem correta</li>
</ul>

#### 3- Programar o ESP32:
<ul>
    <li>Abra o Arduino IDE e crie um novo sketch.</li>
    <li>Inclua as bibliotecas necessárias no início do código.</li>
</ul>

      ```
        #include <Adafruit_Sensor.h>
        #include <DHT.h>
        #include <DHT_U.h>
      ```
<ul>
    <li>Defina as constantes para o pino de dados do DHT22 e o tipo de sensor.</li>
</ul>

    ```
        #define DHTPIN 1      // Pino de dados do DHT22 conectado ao pino D1 no ESP32
        #define DHTTYPE DHT22 // Tipo de sensor DHT22

      ```

<ul>
    <li>Crie uma instância do sensor DHT.</li>
</ul>

    ```
        DHT_Unified dht(DHTPIN, DHTTYPE);
      ```
<ul>
    <li>No método setup(), inicialize o sensor.</li>
</ul>

      ```
        void setup() {
          Serial.begin(115200);
          dht.begin();
        }

      ```

<ul>
    <li>No método loop(), leia os valores de temperatura e umidade e imprima-os no monitor serial.</li>
</ul>
      
      ```
        void loop() {
            sensors_event_t event;
            dht.temperature().getEvent(&event);
        
            if (isnan(event.temperature)) {
                Serial.println("Erro ao ler temperatura!");
            } else {
                Serial.print("Temperatura: ");
                Serial.print(event.temperature);
                Serial.println(" °C");
            }
        
            dht.humidity().getEvent(&event);
        
            if (isnan(event.relative_humidity)) {
                Serial.println("Erro ao ler umidade!");
            } else {
                Serial.print("Umidade: ");
                Serial.print(event.relative_humidity);
                Serial.println(" %");
            }
        
            delay(2000); // Espere 2 segundos antes de ler novamente
        }
              
      ```

#### 4- Upload e Monitoramento:
<ul>
    <li>Compile e faça o upload do código para o seu ESP32.</li>
    <li>Abra o Monitor Serial (Tools -> Serial Monitor) para ver os valores de temperatura e umidade sendo lidos a cada 2 segundos.</li>
</ul>

## Simulação do projeto
https://wokwi.com/projects/382304674782635009

## Link para o vídeo
aqui

## Copyright

ATENÇÃO: O programa deve ser utilizado EXCLUSIVAMENTE como forma de estudos para aqueles que baixarem sem serem as desenvolvedoras. <br>

Copyright ©️ Anny.
