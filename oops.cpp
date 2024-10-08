#include <iostream>
#include <string>
#include <vector>

// Base class: WeatherData
class WeatherData {
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
    ~WeatherData() {
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
};

// Initialize static member variable
int WeatherData::instanceCount = 0;

// Derived class: AdvancedWeatherData demonstrating Single Inheritance
class AdvancedWeatherData : public WeatherData {
private:
    std::string location;

public:
    // Parameterized constructor with additional parameter for location
    AdvancedWeatherData(double temp, double hum, double wind, bool precipitation, const std::string& loc)
        : WeatherData(temp, hum, wind, precipitation), location(loc) {}

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

    // Display method
    void displayWeatherInfo() const {
        std::cout << "Location: " << location << std::endl;
        std::cout << "Temperature: " << temperature << "°C" << std::endl;
        std::cout << "Humidity: " << humidity << "%" << std::endl;
        std::cout << "Wind Speed: " << windSpeed << " km/h" << std::endl;
        std::cout << "Precipitation: " << (isPrecipitation ? "Yes" : "No") << std::endl;
    }
};

// Base class: WeatherPredictor
class WeatherPredictor {
protected:
    static std::vector<std::string> defaultClothesSunny;
    static std::vector<std::string> defaultClothesRainy;
    static std::vector<std::string> defaultClothesSnowy;
    static std::vector<std::string> defaultClothesCloudy;
    static std::vector<std::string> defaultFoodSunny;
    static std::vector<std::string> defaultFoodRainy;
    static std::vector<std::string> defaultFoodSnowy;
    static std::vector<std::string> defaultFoodCloudy;

public:
    static std::string predictClimate(const WeatherData& data) {
        if (data.getIsPrecipitation()) {
            if (data.getTemperature() <= 0) return "Snowy";
            else return "Rainy";
        } else if (data.getTemperature() > 25 && data.getHumidity() < 60) {
            return "Sunny";
        } else if (data.getTemperature() < 10) {
            return "Cold";
        } else {
            return "Cloudy";
        }
    }

    static std::vector<std::string> suggestClothes(const std::string& climate) {
        if (climate == "Snowy") return defaultClothesSnowy;
        if (climate == "Rainy") return defaultClothesRainy;
        if (climate == "Sunny") return defaultClothesSunny;
        return defaultClothesCloudy;
    }

    static std::vector<std::string> suggestFood(const std::string& climate) {
        if (climate == "Snowy") return defaultFoodSnowy;
        if (climate == "Rainy") return defaultFoodRainy;
        if (climate == "Sunny") return defaultFoodSunny;
        return defaultFoodCloudy;
    }
};

// Derived class: SeasonalWeatherPredictor demonstrating Single Inheritance
class SeasonalWeatherPredictor : public WeatherPredictor {
public:
    static std::string getSeasonalRecommendation(const std::string& climate) {
        if (climate == "Snowy" || climate == "Cold") return "Stay indoors and keep warm!";
        if (climate == "Rainy") return "Carry an umbrella or raincoat.";
        if (climate == "Sunny") return "Stay hydrated and avoid direct sunlight.";
        return "It's a calm day; enjoy your time outside.";
    }
};

// Derived class: ExtendedSeasonalWeatherPredictor demonstrating Multilevel Inheritance
class ExtendedSeasonalWeatherPredictor : public SeasonalWeatherPredictor {
public:
    static std::string getActivitySuggestion(const std::string& climate) {
        if (climate == "Snowy") return "Great day for skiing!";
        if (climate == "Rainy") return "Perfect for indoor games or movies.";
        if (climate == "Sunny") return "Consider a picnic or a beach visit.";
        return "Ideal day for a walk or a short hike.";
    }
};

// Initialize static member variables of WeatherPredictor class
std::vector<std::string> WeatherPredictor::defaultClothesSunny = {"Light shirt", "Sunglasses", "Hat"};
std::vector<std::string> WeatherPredictor::defaultClothesRainy = {"Raincoat", "Umbrella", "Waterproof shoes"};
std::vector<std::string> WeatherPredictor::defaultClothesSnowy = {"Warm coat", "Scarf", "Gloves", "Boots"};
std::vector<std::string> WeatherPredictor::defaultClothesCloudy = {"Light jacket", "Comfortable shoes"};
std::vector<std::string> WeatherPredictor::defaultFoodSunny = {"Salad", "Cold drinks", "Ice cream"};
std::vector<std::string> WeatherPredictor::defaultFoodRainy = {"Comfort food", "Hot chocolate", "Grilled cheese sandwich"};
std::vector<std::string> WeatherPredictor::defaultFoodSnowy = {"Hot soup", "Warm tea", "Stew"};
std::vector<std::string> WeatherPredictor::defaultFoodCloudy = {"Balanced meal", "Fruit"};

// Main function to demonstrate the usage of the inheritance concept
int main() {
    // Create instances using the derived class AdvancedWeatherData
    AdvancedWeatherData advWeather1(5.0, 70.0, 10.0, true, "New York");
    AdvancedWeatherData advWeather2;

    // Manual input for the second instance
    std::cout << "\nEnter weather data for day 2:\n";
    advWeather2.getInput();

    // Display weather information and get predictions
    std::cout << "\n--- Day 1 Weather Information ---\n";
    advWeather1.displayWeatherInfo();

    std::string climate1 = WeatherPredictor::predictClimate(advWeather1);
    std::cout << "Predicted Climate: " << climate1 << std::endl;
    std::cout << "Seasonal Recommendation: " << SeasonalWeatherPredictor::getSeasonalRecommendation(climate1) << std::endl;
    std::cout << "Activity Suggestion: " << ExtendedSeasonalWeatherPredictor::getActivitySuggestion(climate1) << std::endl;

    std::cout << "\n--- Day 2 Weather Information ---\n";
    advWeather2.displayWeatherInfo();

    std::string climate2 = WeatherPredictor::predictClimate(advWeather2);
    std::cout << "Predicted Climate: " << climate2 << std::endl;
    std::cout << "Seasonal Recommendation: " << SeasonalWeatherPredictor::getSeasonalRecommendation(climate2) << std::endl;
    std::cout << "Activity Suggestion: " << ExtendedSeasonalWeatherPredictor::getActivitySuggestion(climate2) << std::endl;

    return 0;
}
