#include <WiFi.h>
#include <HTTPClient.h>
#include <esp32cam.h>
#include <Base64.h>

// Credenciais de WiFi
const char* WIFI_SSID = "nome_do_wifi";
const char* WIFI_PASS = "senha_do_wifi";

// endpoint da api
const char* serverUrl = "http://192.168.1.40:8080/imagens";

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Config câmera
    {
        using namespace esp32cam;
        Config cfg;
        cfg.setPins(pins::AiThinker);  
        cfg.setResolution(Resolution::find(640, 480));  // define resolução que vai ser utilizada
        // cfg.setResolution(Resolution::find(1280, 800));  // define resolução que vai ser utilizada
        cfg.setBufferCount(2);
        cfg.setJpeg(80); // define a qualidade da imagem jpeg

        if (!Camera.begin(cfg)) {
            Serial.println("Falha na inicialização da câmera");
            return;
        }
    }

    // config WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado ao WiFi!");
    Serial.print("IP do ESP32-CAM: ");
    Serial.println(WiFi.localIP());
}

bool captureAndSendImage() {
    // Captura imagem
    auto img = esp32cam::capture();
    if (!img) {
        Serial.println("Falha na captura da imagem");
        return false;
    }

    // organizar o cabeçalho da requisição
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "image/jpeg");

    // envia imagem como binário
    // verificar se o size é constante
    int httpResponseCode = http.POST(img->data(), img->size());
    
    Serial.print("Código de Resposta HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Resposta do Servidor:");
        Serial.println(response);
    } else {
        Serial.print("Erro no POST HTTP: ");
        Serial.println(http.errorToString(httpResponseCode));
    }

    http.end();
    return httpResponseCode > 0;
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nCapturando e enviando imagem...");
        
        if (captureAndSendImage()) {
            Serial.println("Imagem enviada com sucesso");
        } else {
            Serial.println("Falha ao enviar imagem");
        }
    } else {
        Serial.println("WiFi desconectado");
    }
    delay(10000);
}