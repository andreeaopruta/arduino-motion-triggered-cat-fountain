const int PIN_PIR = 2;     // PIR sensor OUT pin
const int PIN_RELAY = 3;   // Relay IN pin

unsigned long lastMotionTime = 0; // Stores the timestamp of the last detected motion
const unsigned long RUN_TIME = 30000; // Time the pump runs after the cat leaves (30 seconds)

bool isPumpRunning = false; // Stores the current state of the pump

void setup() {
  Serial.begin(9600);            
  
  pinMode(PIN_PIR, INPUT); 
  pinMode(PIN_RELAY, OUTPUT);
  
  // Ensure the relay is off at startup
  digitalWrite(PIN_RELAY, LOW); 

  Serial.println("Calibrating PIR sensor (15 seconds)...");
  // The PIR sensor needs time to read the room's thermal signature
  delay(15000); 
  
  Serial.println("Fountain System is READY!");
}

void loop() {
  int currentPirState = digitalRead(PIN_PIR);

  // If the sensor detects motion (sends HIGH)
  if (currentPirState == HIGH) {   
    lastMotionTime = millis(); // Reset the timer
    
    // If the pump was off, turn it on
    if (!isPumpRunning) {
      Serial.println("Cat arrived! Pump ON.");
      digitalWrite(PIN_RELAY, HIGH);
      isPumpRunning = true;
    }
  }
  
  // Check if the pump is running and if the time since the last motion has expired
  if (isPumpRunning && (millis() - lastMotionTime >= RUN_TIME)) {
    Serial.println("Cat left. Pump OFF.");
    digitalWrite(PIN_RELAY, LOW);  
    isPumpRunning = false;
  }
}
