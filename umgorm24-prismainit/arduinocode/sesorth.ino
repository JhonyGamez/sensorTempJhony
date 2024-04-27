#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN 4     // Pin GPIO donde está conectado el pin de datos del DHT11
#define DHTTYPE DHT11 // Tipo de sensor DHT que estás utilizando (DHT11 o DHT22)

const char* ssid = "Galaxy S23 AF32";  //NOMBRE RED WIFI
const char* password =  "09583981"; // CONTRASEÑA RED WIFI
const char* serverName = "http://192.168.79.227:3001/datos"; 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }

  Serial.println("Conectado al WiFi");
  dht.begin();
}

void loop() {
  // Lectura del sensor
  float temperatura = dht.readTemperature(); // Leer temperatura en grados Celsius
  float humedad = dht.readHumidity();        // Leer humedad relativa en porcentaje

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Leer el caracter recibido por el puerto serial
    
    if (receivedChar == 'v' || receivedChar == 'V') {
      // Crear un objeto JSON para enviar al servidor
      DynamicJsonDocument doc(200);
      doc["nombrecompleto"] = "Jhonatan Gamez";
      doc["correouniversidad"] = "jterrong@miumg.edu.gt";
      doc["carne"] = "0902-17-7398";
      doc["Latitud"] = "10.12345";
      doc["Logitud"] = "-84.12345";
      doc["Humedad"] = humedad;
      doc["Temperatura"] = temperatura;

      // Serializar el JSON a una cadena
      String jsonString;
      serializeJson(doc, jsonString);

      // Realizar la solicitud HTTP POST
      HTTPClient http;
      http.begin(serverUrl);                  // Especificar la URL del endpoint
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(jsonString);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        String response = http.getString();
        Serial.println(response);
      } else {
        Serial.print("Error en la solicitud HTTP: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    }
  }

  // Esperar un corto tiempo antes de verificar de nuevo la tecla presionada
  delay(100);
}