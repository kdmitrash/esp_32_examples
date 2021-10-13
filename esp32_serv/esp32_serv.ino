#include <WebServer.h>

// #include "DHT.h"
// ���������������� �� ������, ������� ������������� ������ �������
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const char* ssid = "Test_ESP32";  // ������ ���� SSID
const char* password = "Test_ESP32";  //������ ������

WebServer server(80);

float Temperature = 21;
float Humidity = 90;

void setup() {
	Serial.begin(115200);
	delay(100);

	Serial.println("Connecting to ");
	Serial.println(ssid);

	//������������ � WiFi
	WiFi.begin(ssid, password);

	//��������� �����������
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}
Serial.println("");
Serial.println("WiFi connected..!");
Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

server.on("/", handle_OnConnect);
server.onNotFound(handle_NotFound);

server.begin();
Serial.println("HTTP server started");

}
void loop() {

server.handleClient();

}

void handle_OnConnect() {

Temperature = dht.readTemperature(); // �������� �������� �����������
Humidity = dht.readHumidity(); // �������� ��������� ���������
server.send(200, "text/html", SendHTML(Temperature,Humidity));
}

void handle_NotFound(){
server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
String ptr = "<!DOCTYPE html> <html>\n";
ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
ptr +="<title>ESP32 Weather Report</title>\n";
ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
ptr +="</style>\n";
ptr +="</head>\n";
ptr +="<body>\n";
ptr +="<div id=\"webpage\">\n";
ptr +="<h1>ESP32 Weather Report</h1>\n";

ptr +="<p>Temperature: ";
ptr +=(int)Temperaturestat;
ptr +="�C</p>";
ptr +="<p>Humidity: ";
ptr +=(int)Humiditystat;
ptr +="%</p>";

ptr +="</div>\n";
ptr +="</body>\n";
ptr +="</html>\n";
return ptr;
}
