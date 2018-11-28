#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST " "
#define FIREBASE_AUTH " "
#define WIFI_SSID " "
#define WIFI_PASSWORD " "                                     //Password of your wifi network 

#define Relay1 05 //D6
int val1;

#define Relay2 04 //D2
int val2;

#define Relay3 00  //D1
int val3;

#define Relay4 02 //D5
int val4;

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  digitalWrite(Relay3,LOW);
  digitalWrite(Relay4,LOW);



  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
  }

void loop() 
{
  String path = "/room1";
  FirebaseObject object = Firebase.get(path);
  
  if (Firebase.failed())
      {
      Serial.print("Failed to connect with server");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }


  val1 = object.getInt("S1");
                                        //Reading the value of the varialble Status from the firebase
  if(val1==1)                                                             // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,LOW);
      Serial.println(val1);
    }
    else if(val1==0)                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println(val1);
    }

  val2=object.getInt("S2");                                        //Reading the value of the varialble Status from the firebase
  
  if(val2==1)                                                             // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("light 2 ON");
    }
    else if(val2==0)                                                      // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("light 2 OFF");
    }

   val3=object.getInt("S3");                                        //Reading the value of the varialble Status from the firebase
  
  if(val3==1)                                                             // If, the Status is 1, turn on the Relay3
     {
      digitalWrite(Relay3,LOW);
      Serial.println("light 3 ON");
    }
    else if(val3==0)                                                      // If, the Status is 0, turn Off the Relay3
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("light 3 OFF");
    }

   val4=object.getInt("S4");                                        //Reading the value of the varialble Status from the firebase
   
  if(val4==1)                                                             // If, the Status is 1, turn on the Relay4
     {
      digitalWrite(Relay4,LOW);
      Serial.println("light 4 ON");
    }
    else if(val4==0)                                                      // If, the Status is 0, turn Off the Relay4
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("light 4 OFF");
   }    
}
