#include <iostream>
#include <string>
#include <vector>

// Abstraction through the WeatherData class: 
// This class hides the details of how weather data is stored (temperature, humidity, etc.) and provides methods to access and modify the data.
class WeatherData {
private:
    double temperature;
    double humidity;
    double windSpeed;
    bool isPrecipitation;

    // Static member variable to count the number of WeatherData instances
    static int instanceCount;

public:
    // Constructor to initialize data and increment instance count
    WeatherData() : temperature(0), humidity(0), windSpeed(0), isPrecipitation(false) {
        instanceCount++;
    }

    // Destructor to decrement instance count
    ~WeatherData() {
        instanceCount--;
    }

    // Abstraction through encapsulation of data:
    // These setter methods abstract the process of modifying the member variables.
    void setTemperature(double temp) { this->temperature = temp; }
    void setHumidity(double hum) { this->humidity = hum; }
    void setWindSpeed(double wind) { this->windSpeed = wind; }
    void setIsPrecipitation(bool precipitation) { this->isPrecipitation = precipitation; }

    // Abstraction through encapsulation of access:
    // These getter methods abstract how the data is retrieved.
    double getTemperature() const { return this->temperature; }
    double getHumidity() const { return this->humidity; }
    double getWindSpeed() const { return this->windSpeed; }
    bool getIsPrecipitation() const { return this->isPrecipitation; }

    // Static method to get the instance count - an abstraction of how instance counting works
    static int getInstanceCount() {
        return instanceCount;
    }

    // A method to encapsulate the input operation
    // The process of collecting user input is abstracted into a single method, hiding the details of how it's done.
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

// Abstraction through the WeatherPredictor class: 
// This class hides the logic of climate prediction and suggestions and exposes simple methods to interact with it.
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
    // Static method for predicting climate: 
    // This method abstracts the internal logic for determining the climate based on weather data.
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

    // Static method for suggesting clothes:
    // This abstracts the logic of which clothes to recommend for a given climate.
    static std::vector<std::string> suggestClothes(const std::string& climate) {
        if (climate == "Snowy") return defaultClothesSnowy;
        if (climate == "Rainy") return defaultClothesRainy;
        if (climate == "Sunny") return defaultClothesSunny;
        return defaultClothesCloudy;
    }

    // Static method for suggesting food:
    // This abstracts the logic of which food to recommend for a given climate.
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

    // Create an array of WeatherData objects
    WeatherData* weatherDataArray = new WeatherData[NUM_DAYS];
    
    // Collect weather data for each day
    for (int i = 0; i < NUM_DAYS; i++) {
        std::cout << "\nEnter weather data for day " << i + 1 << ":\n";
        weatherDataArray[i].getInput();  // Abstraction: We don't need to know the input details, it's handled internally.
    }
    
    // Predict climate and suggest clothes/food for each day
    for (int i = 0; i < NUM_DAYS; i++) {
        std::cout << "\n--- Day " << i + 1 << " Forecast ---\n";
        std::string climate = WeatherPredictor::predictClimate(weatherDataArray[i]);  // Abstraction of prediction logic
        std::vector<std::string> clothes = WeatherPredictor::suggestClothes(climate); // Abstraction of suggestion logic
        std::vector<std::string> foods = WeatherPredictor::suggestFood(climate);      // Abstraction of suggestion logic
        
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
