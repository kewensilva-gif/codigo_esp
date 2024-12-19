## Configuração do ambiente com arduino IDE

Faça o clone do projeto e abra a o arduino IDE para os próximos passos.

### Instalação da biblioteca esp32cam
1. Baixe o zip do seguinte repositório: 
https://github.com/yoursunny/esp32cam // Ele se refere a biblioteca esp32cam.h.

2. Na parte superior da arduino IDE e siga o seguinte caminho: 
Sketch > Include library > add .zip library;
3. Selecione o arquivo zip que foi baixado;
4. No output deve aparecer "Library installed".

### Selecionando Board
1. Na parte superior da arduino IDE e siga o seguinte caminho: 
Tools > Board > esp32 > ESP32 Wrover Module.

### Selecionando a porta
1. Na parte superior da arduino IDE e siga o seguinte caminho: 
Tools > Port;
2. Conecte o microcontrolador e verifique se aparece alguma porta, caso não, teste as portas disponíveis.

### Configurando conexão wifi
1. No código principal, edite as variáveis WIFI_SSID E WIFI_PASS com as suas credenciais de wifi

### Configurando Serial monitor
1. No parte superior direita da arduino IDE, clique no botão de lupa;
2. O monitor serial vai abrir na parte inferior;
3. No canto direito defina como 115200 baud.

### Upload
1. Na parte superior da arduino IDE selecione a opção de upload;
2. Quando o processo for finalizado aperte o botão 'rst' do micro e verifique o Serial monitor.
