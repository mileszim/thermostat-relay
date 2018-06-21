#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <MCP9808.h>


class Temperature {
    public:
        Temperature();
        virtual ~Temperature();

        double temp();
        double temperature();
        double tempCelcius();

        bool updateCurrentTemperatures();

    private:
        double _tempCelcius = 0.0;
        double _tempFahrenheit = 0.0;
        MCP9808* _mcp;
        double _toFahrenheit(double tempCelcius);
        bool _publishTemp();
        double _getTemperature();
};


#endif
