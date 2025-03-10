#define SENSOR_PIN A0
#define LED_PIN 12
#define BUZZER_PIN 10

#define THRESHOLD_VALUE 690
#define ALERT_INTERVAL 1000
#define SERIAL_SPEED 9600

unsigned long lastAlertTime = 0;
bool alarmState = false;

void setup() {
  Serial.begin(SERIAL_SPEED);
  
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Started");
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  
  Serial.print("Sensor Reading: " + sensorValue);
  
  if (sensorValue > THRESHOLD_VALUE) {
    waterDetected();
  } else {
    waterNotDetected();
  }
  
  delay(200);
}

void waterDetected() {
  digitalWrite(LED_PIN, HIGH);
  
  unsigned long currentTime = millis();
  
  if (currentTime - lastAlertTime >= ALERT_INTERVAL) {
    lastAlertTime = currentTime;

    tone(BUZZER_PIN, 1000, 200);
    
    if (!alarmState) {
      Serial.println("ALERT! Water detected!");
      alarmState = true;
    }
  }
}

void waterNotDetected() {
  digitalWrite(LED_PIN, LOW);
  
  if (alarmState) {
    Serial.println("System normalized: no water detected.");
    alarmState = false;
  }
}