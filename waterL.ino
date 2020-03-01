


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "www.firebaseiso.com" // host name
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" // auth key
#define WIFI_SSID "xxxxx"
#define WIFI_PASSWORD "xxxx"

WiFiClient client;

int led1=16;

const int trigPin = 5;  //D1
const int echoPin = 4;  //D2 
//vin-vcc
//gnd-gnd
long duration;
float distance;
float percentage;
float percentage2;
String fireStatus; 

void setup() {
  // put your setup code here, to run once:

  pinMode(led1,OUTPUT); //MOTOR
 

  Serial.begin(9600);
  pinMode(trigPin,OUTPUT); 
  pinMode(echoPin,INPUT);  
   
  // connect to wifi.
  pinMode(D3,OUTPUT);  //D3
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);



  

}

void loop() {
  // put your main code here, to run repeatedly:

    //    heightTank=151;  height of the tank
    //  deviation=29;  distance between max level and tank top level
//-------------------------------------------
//WATER LEVEL AUTOMATION
//-------------------------------------------
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
 percentage=25-distance;
 percentage2=5*percentage;
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
     Firebase.setInt("DISTANCE",distance);
     
     
 
   Firebase.setInt("LEVEL",percentage2);
  
  String statuss1=String("MOTOR ON");
  String statuss2=String("MOTOR OFF");

            if(distance<=6)
                          {
                           Serial.print("MOTOR OFF\n");
                           digitalWrite(led1,HIGH);  
             
               
                  
                        Firebase.setString("MOTOR",statuss2);
                        }
              else if(distance>=20)
                   {
                   Serial.print("MOTOR ON\n");
                   digitalWrite(led1,LOW);  
                   Firebase.setString("MOTOR",statuss1);
                   }


  delay(1000);     
  }




 
