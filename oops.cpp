#include <iostream>
#include <string>
#include <vector>

// Abstract base class: WeatherDisplay
class WeatherDisplay {
public:
    // Pure virtual function making this an abstract class
    virtual void displayWeatherInfo() const = 0;

    // Virtual destructor
    virtual ~WeatherDisplay() {}
};

// Base class: WeatherData
class WeatherData : public WeatherDisplay {
protected:
    double temperature;
    double humidity;
    double windSpeed;
    bool isPrecipitation;

    // Static member variable to count the number of WeatherData instances
    static int instanceCount;

public:
    // Default constructor
    WeatherData() : temperature(0), humidity(0), windSpeed(0), isPrecipitation(false) {
        instanceCount++;
    }

    // Parameterized constructor
    WeatherData(double temp, double hum, double wind, bool precipitation)
        : temperature(temp), humidity(hum), windSpeed(wind), isPrecipitation(precipitation) {
        instanceCount++;
    }

    // Destructor
    ~WeatherData() override {
        instanceCount--;
    }

    // Setter methods
    void setTemperature(double temp) { this->temperature = temp; }
    void setHumidity(double hum) { this->humidity = hum; }
    void setWindSpeed(double wind) { this->windSpeed = wind; }
    void setIsPrecipitation(bool precipitation) { this->isPrecipitation = precipitation; }

    // Getter methods
    double getTemperature() const { return this->temperature; }
    double getHumidity() const { return this->humidity; }
    double getWindSpeed() const { return this->windSpeed; }
    bool getIsPrecipitation() const { return this->isPrecipitation; }

    // Static method to get the instance count
    static int getInstanceCount() {
        return instanceCount;
    }

    // Input method for manual data entry
    void getInput() {
        std::cout << "Enter temperature (°C): ";
        std::cin >> this->temperature;
        std::cout << "Enter humidity (%): ";
        std::cin >> this->humidity;
        std::cout << "Enter wind speed (km/h): ";
        std::cin >> this->windSpeed;
        std::cout << "Is there precipitation? (1 for yes, 0 for no): ";
        std::cin >> this->isPrecipitation;
    }

    // Implementation of pure virtual function from WeatherDisplay
    void displayWeatherInfo() const override {
        std::cout << "Temperature: " << temperature << "°C" << std::endl;
        std::cout << "Humidity: " << humidity << "%" << std::endl;
        std::cout << "Wind Speed: " << windSpeed << " km/h" << std::endl;
        std::cout << "Precipitation: " << (isPrecipitation ? "Yes" : "No") << std::endl;
    }
};

// Initialize static member variable
int WeatherData::instanceCount = 0;

// Derived class: AdvancedWeatherData demonstrating Single Inheritance and Function Overloading
class AdvancedWeatherData : public WeatherData {
private:
    std::string location;

public:
    // Parameterized constructor with additional parameter for location
    AdvancedWeatherData(double temp, double hum, double wind, bool precipitation, const std::string& loc)
        : WeatherData(temp, hum, wind, precipitation), location(loc) {}

    // Default constructor
    AdvancedWeatherData() : WeatherData(), location("Unknown") {}

    // Setter for location
    void setLocation(const std::string& loc) { this->location = loc; }

    // Getter for location
    std::string getLocation() const { return this->location; }

    // Overriding getInput method to include location input
    void getInput() {
        WeatherData::getInput();  // Call base class method
        std::cout << "Enter location: ";
        std::cin >> this->location;
    }

    // Overriding displayWeatherInfo from WeatherData and WeatherDisplay
    void displayWeatherInfo() const override {
        std::cout << "Location: " << location << std::endl;
        WeatherData::displayWeatherInfo();  // Call base class method
    }

    // Function Overloading: Display method with different parameters

    // 1. Display weather information with an additional title
    void displayWeatherInfo(const std::string& title) const {
        std::cout << "\n--- " << title << " ---\n";
        displayWeatherInfo();  // Call the default display method
    }

    // 2. Display weather information with all parameters explicitly
    void displayWeatherInfo(double temp, double hum, double wind, bool precipitation) const {
        std::cout << "Custom Display Mode: " << std::endl;
        std::cout << "Temperature: " << temp << "°C" << std::endl;
        std::cout << "Humidity: " << hum << "%" << std::endl;
        std::cout << "Wind Speed: " << wind << " km/h" << std::endl;
        std::cout << "Precipitation: " << (precipitation ? "Yes" : "No") << std::endl;
    }
};

// Main function to demonstrate the usage of polymorphism, inheritance, abstract class, and virtual functions
int main() {
    // Create a pointer of the abstract base class type pointing to a derived class object
    WeatherDisplay* display1 = new AdvancedWeatherData(5.0, 70.0, 10.0, true, "New York");
    WeatherDisplay* display2 = new AdvancedWeatherData();

    std::cout << "\n--- Day 1 Weather Information ---\n";
    display1->displayWeatherInfo();  // Polymorphic call using base class pointer

    std::cout << "\n--- Day 2 Weather Information (Manual Input) ---\n";
    dynamic_cast<AdvancedWeatherData*>(display2)->getInput();  // Casting to derived type to use derived class method
    display2->displayWeatherInfo();

    // Clean up
    delete display1;
    delete display2;

    return 0;
}
