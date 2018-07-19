//receiver settings
int minSpeed=255;
const int laggingTime = 1000;
const int LED = 13;
int flag = 0;
String readString;

//L293D
//Motor A, C
const int motorPin1  = 9;  
const int motorPin2  = 10; 
//Motor B, D   
const int motorPin3  = 6; 
const int motorPin4  = 5; 

//This will run only one time.
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);    
    
  //Set motor pins as outputs   
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  //if some date is sent, reads it and saves in state
  while (Serial.available() > 0) {
    char intToChar = Serial.read();
    readString += intToChar;
    delay(5);
  }  

  if (readString == "F") {
      moveForward(minSpeed);
//      Serial.println(readString);
    } else if (readString == "B") {
     moveBackward(minSpeed);
//     Serial.println(readString);
   } else if (readString == "L") {
     turnLeft(minSpeed);
//     Serial.println(readString);
   } else if (readString == "R") {
     turnRight(minSpeed);
//     Serial.println(readString);
   } else if (readString == "on") {
     digitalWrite(LED, HIGH);
     Serial.println(readString);     
   } else if (readString == "off") {
     digitalWrite(LED, LOW);     
     Serial.println(readString);     
   } else if (readString == "f" || readString == "b" || readString == "l" || readString == "r") {
     readString = "";
     stop();
   } else if (readString.length() > 0 && (readString.toInt()) > 0) {
    if (minSpeed > 255) {
      minSpeed = 255;  
    } else {
      minSpeed = readString.toInt();
    }
    Serial.println(minSpeed);  
   }
   
   if (readString.length() > 0 ) {
    readString = "";
  }
}

void moveBackward(int signal) {
  Serial.println("backward");    
  analogWrite(motorPin2, signal);      
  analogWrite(motorPin4, signal); 
}

void moveForward(int signal) {
  Serial.println("forward");  
  analogWrite(motorPin1, signal);      
  analogWrite(motorPin3, signal);     
}

void turnRight(int signal) {
  Serial.println("turn right"); 
  analogWrite(motorPin2, signal);      
  analogWrite(motorPin3, signal);
}

void turnLeft(int signal) {
  Serial.println("turn left"); 
  analogWrite(motorPin1, signal);      
  analogWrite(motorPin4, signal); 
}

void stop() {
  Serial.println("stop\n");        
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);  
}

