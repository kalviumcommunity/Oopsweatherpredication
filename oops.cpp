#include <iostream>
#include <string>
#include <vector>

class WeatherData {
private:
    double temperature;
    double humidity;
    double windSpeed;
    bool isPrecipitation;

    // Static member variable to count the number of WeatherData instances
    static int instanceCount;

public:
    WeatherData() : temperature(0), humidity(0), windSpeed(0), isPrecipitation(false) {
        instanceCount++;
    }

    ~WeatherData() {
        instanceCount--;
    }

    // Setter methods to encapsulate the modification of member variables
    void setTemperature(double temp) { this->temperature = temp; }
    void setHumidity(double hum) { this->humidity = hum; }
    void setWindSpeed(double wind) { this->windSpeed = wind; }
    void setIsPrecipitation(bool precipitation) { this->isPrecipitation = precipitation; }

    // Getter methods to encapsulate access to member variables
    double getTemperature() const { return this->temperature; }
    double getHumidity() const { return this->humidity; }
    double getWindSpeed() const { return this->windSpeed; }
    bool getIsPrecipitation() const { return this->isPrecipitation; }

    static int getInstanceCount() {
        return instanceCount;
    }

    // A method to encapsulate the input operation
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

class WeatherPredictor {
private:
    // Static member variables for default recommendations
    static std::vector<std::string> defaultClothesSunny;
    static std::vector<std::string> defaultClothesRainy;
    static std::vector<std::string> defaultClothesSnowy;
    static std::vector<std::string> defaultClothesCloudy;
    static std::vector<std::string> defaultFoodSunny;
    static std::vector<std::string> defaultFoodRainy;
    static std::vector<std::string> defaultFoodSnowy;
    static std::vector<std::string> defaultFoodCloudy;

public:
    // Pass by reference instead of raw pointer
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

// Initialize static member variables
std::vector<std::string> WeatherPredictor::defaultClothesSunny = {"Light shirt", "Sunglasses", "Hat"};
std::vector<std::string> WeatherPredictor::defaultClothesRainy = {"Raincoat", "Umbrella", "Waterproof shoes"};
std::vector<std::string> WeatherPredictor::defaultClothesSnowy = {"Warm coat", "Scarf", "Gloves", "Boots"};
std::vector<std::string> WeatherPredictor::defaultClothesCloudy = {"Light jacket", "Comfortable shoes"};
std::vector<std::string> WeatherPredictor::defaultFoodSunny = {"Salad", "Cold drinks", "Ice cream"};
std::vector<std::string> WeatherPredictor::defaultFoodRainy = {"Comfort food", "Hot chocolate", "Grilled cheese sandwich"};
std::vector<std::string> WeatherPredictor::defaultFoodSnowy = {"Hot soup", "Warm tea", "Stew"};
std::vector<std::string> WeatherPredictor::defaultFoodCloudy = {"Balanced meal", "Fruit"};

int main() {
    const int NUM_DAYS = 3;

    // Dynamically allocate memory for the WeatherData array
    WeatherData* weatherDataArray = new WeatherData[NUM_DAYS];
    
    for (int i = 0; i < NUM_DAYS; i++) {
        std::cout << "\nEnter weather data for day " << i + 1 << ":\n";
        weatherDataArray[i].getInput();
    }
    
    for (int i = 0; i < NUM_DAYS; i++) {
        std::cout << "\n--- Day " << i + 1 << " Forecast ---\n";
        std::string climate = WeatherPredictor::predictClimate(weatherDataArray[i]);
        std::vector<std::string> clothes = WeatherPredictor::suggestClothes(climate);
        std::vector<std::string> foods = WeatherPredictor::suggestFood(climate);
        
        std::cout << "Predicted climate: " << climate << std::endl;
        
        std::cout << "Suggested clothes:" << std::endl;
        for (const auto& item : clothes) {
            std::cout << "- " << item << std::endl;
        }
        
        std::cout << "Suggested foods:" << std::endl;
        for (const auto& item : foods) {
            std::cout << "- " << item << std::endl;
        }
    }

    // Clean up dynamically allocated memory
    delete[] weatherDataArray;

    return 0;
}
