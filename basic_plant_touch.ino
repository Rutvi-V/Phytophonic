#include <CapacitiveSensor.h>

// Capacitive sensor setup
CapacitiveSensor Sensor1 = CapacitiveSensor(4, 6);
long val1;

// Rain sensor setup
#define rainSensorPin 13
int rainSensorState = 0;

int pos = 0;
#define buzzer 8

void setup() {
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(rainSensorPin, INPUT);
}

void loop() {
    val1 = Sensor1.capacitiveSensor(100); //Increase sample time
    rainSensorState = digitalRead(rainSensorPin); // Read rain sensor state

    Serial.print("Capacitive Sensor Value: ");
    Serial.print(val1);
    Serial.print("\t Rain Sensor State: ");
    Serial.println(rainSensorState);

    delay(100); // Increase delay to prevent flooding

    // Check if the rain sensor is not detecting rain
    if (rainSensorState == HIGH) { // Assuming HIGH means no rain
        // Check capacitive sensor value
        if (val1 >= 300 && pos == 0) {
            digitalWrite(buzzer, HIGH);
            delay(500);
            digitalWrite(buzzer, LOW);
            pos = 1;
            delay(100);
        } else if (val1 >= 300 && pos == 1) {
            pos = 0;
            delay(500);
        }
    } else {
        // If it's raining, ensure the buzzer is off
        digitalWrite(buzzer, LOW);
    }

    delay(10);
}