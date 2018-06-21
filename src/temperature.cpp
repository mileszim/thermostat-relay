#include "temperature.h"


/**
 * Constructor/Deconstructor
 * @params none
 * @returns Temperature
 */
Temperature::Temperature() {
    _mcp = new MCP9808();
    // Wait for initialization
	while (!_mcp->begin()) {
	    Particle.publish("Waiting on MCP9808");
	    delay(500);
	}
	// Sensor reading speed
	_mcp->setResolution(MCP9808_SLOWEST);
}

Temperature::~Temperature() {
    // delete _tempCelcius;
    // delete _tempFahrenheit;
    // delete _mcp;
}


/**
 * Get the current temperature reading
 * @params {none}
 * @returns {double} The temperature in celcius
 */
double Temperature::_getTemperature() {
    _tempCelcius = _mcp->getTemperature();
    return _tempCelcius;
}


/**
 * Convert the temperature to fahrenheit
 * @params
 * @returns double
 */
double Temperature::_toFahrenheit(double celciusTemp) {
    return (celciusTemp * 1.8) + 32.0;
}


/**
 * Get the current temperature in Fahrenheit
 * @params {none}
 * @returns {double}
 */
double Temperature::temp() {
    return _tempFahrenheit;
}


/**
 * Alias for ::temp() {
 * @params {none}
 * @return {double}
 */
double Temperature::temperature() {
    return _tempFahrenheit;
}


/**
 * Return the current temperature in Celcius {
 * @params {none}
 * @return {double}
 */
double Temperature::tempCelcius() {
    return _tempCelcius;
}


/**
 * Function
 * @params {none}
 * @returns {bool}
 */
bool Temperature::updateCurrentTemperatures() {
    _getTemperature();
    _tempFahrenheit = _toFahrenheit(_tempCelcius);
    return 1; // TODO: Update if error
}
