#include <RelayShield.h>
#include "temperature.h"


// Init
const int PUBLISH_INTERVAL = 60; // Seconds

RelayShield relays;
Temperature* temperature = new Temperature();

int turnOnFan(String args);
int turnOffFan(String args);
int turnOnHeater(String args);
int turnOffHeater(String args);
int turnOnAC(String args);
int turnOffAC(String args);


// Main
void setup() {
    Serial.begin(9600);
    delay(5000);
    relays.begin();

    // Set cloud endpoints
    Particle.variable("temp_f", temperature->temp());
    Particle.variable("temp_c", temperature->tempCelcius());

    Particle.function("turnOnFan", turnOnFan);
    Particle.function("turnOffFan", turnOffFan);
    Particle.function("turnOnHeater", turnOnHeater);
    Particle.function("turnOffHeater", turnOffHeater);
    Particle.function("turnOnAC", turnOnAC);
    Particle.function("turnOffAC", turnOffAC);

    // Ready to go
	Particle.publish("Thermostat Relays Ready");
}

void loop() {
    delay(PUBLISH_INTERVAL * 1000);
    temperature->updateCurrentTemperatures();
    publishTemperatureData();
}


// Actions
int turnOnRelay(String command) {
    int num = parseCloudCall(command);
    relays.on(num);
    if (!relays.isOn(num)) { return -1; }
    return 0;
}

int turnOffRelay(String command) {
    int num = parseCloudCall(command);
    relays.off(num);
    if (relays.isOn(num)) { return -1; }
    return 0;
}

int turnOnFan(String args) {
    int num = 1;
    relays.on(num);
    if (!relays.isOn(num)) { return -1; }
    return 0;
}

int turnOffFan(String args) {
    int num = 1;
    relays.off(num);
    if (relays.isOn(num)) { return -1; }
    return 0;
}

int turnOnHeater(String args) {
    int num = 2;
    relays.on(num);
    if (!relays.isOn(num)) { return -1; }
    return 0;
}

int turnOffHeater(String args) {
    int num = 2;
    relays.off(num);
    if (relays.isOn(num)) { return -1; }
    return 0;
}

int turnOnAC(String args) {
    int num = 3;
    relays.on(num);
    if (!relays.isOn(num)) { return -1; }
    return 0;
}

int turnOffAC(String args) {
    int num = 3;
    relays.off(num);
    if (relays.isOn(num)) { return -1; }
    return 0;
}


// Helpers
void publishTemperatureData() {
    double tempCelcius = temperature->tempCelcius();
    double tempFahrenheit = temperature->temp();
    Particle.publish("temp", String(tempFahrenheit));
    Particle.publish("temperature_fahrenheit", String(tempFahrenheit));
    Particle.publish("temperature_celcius", String(tempCelcius));
}

int parseCloudCall(String command) {
    char inputStr[64];
    command.toCharArray(inputStr, 64);
    int i = atoi(inputStr);
    return i;
}
