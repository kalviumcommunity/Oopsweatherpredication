#include <iostream>
#include <string>
#include <vector>

class WeatherData {
private:
    double temperature;
    double humidity;
    double windSpeed;
    bool isPrecipitation;

public:
    WeatherData() : temperature(0), humidity(0), windSpeed(0), isPrecipitation(false) {}

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

    double getTemperature() const { return this->temperature; }
    double getHumidity() const { return this->humidity; }
    double getWindSpeed() const { return this->windSpeed; }
    bool getIsPrecipitation() const { return this->isPrecipitation; }
};

class WeatherPredictor {
public:
    static std::string predictClimate(const WeatherData* data) {
        if (data->getIsPrecipitation()) {
            if (data->getTemperature() <= 0) return "Snowy";
            else return "Rainy";
        } else if (data->getTemperature() > 25 && data->getHumidity() < 60) {
            return "Sunny";
        } else if (data->getTemperature() < 10) {
            return "Cold";
        } else {
            return "Cloudy";
        }
    }

    static std::vector<std::string> suggestClothes(const std::string* climate) {
        std::vector<std::string> clothes;
        if (*climate == "Snowy" || *climate == "Cold") {
            clothes = {"Warm coat", "Scarf", "Gloves", "Boots"};
        } else if (*climate == "Rainy") {
            clothes = {"Raincoat", "Umbrella", "Waterproof shoes"};
        } else if (*climate == "Sunny") {
            clothes = {"Light shirt", "Sunglasses", "Hat"};
        } else {
            clothes = {"Light jacket", "Comfortable shoes"};
        }
        return clothes;
    }

    static std::vector<std::string> suggestFood(const std::string* climate) {
        std::vector<std::string> foods;
        
        if (*climate == "Snowy" || *climate == "Cold") {
            foods = {"Hot soup", "Warm tea", "Stew"};
        } else if (*climate == "Rainy") {
            foods = {"Comfort food", "Hot chocolate", "Grilled cheese sandwich"};
        } else if (*climate == "Sunny") {
            foods = {"Salad", "Cold drinks", "Ice cream"};
        } else {
            foods = {"Balanced meal", "Fruit"};
        }
        return foods;

    }
};

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
        std::string climate = WeatherPredictor::predictClimate(&weatherDataArray[i]);
        std::vector<std::string> clothes = WeatherPredictor::suggestClothes(&climate);
        std::vector<std::string> foods = WeatherPredictor::suggestFood(&climate);
        
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
    
    // Free the dynamically allocated memory
    delete[] weatherDataArray;

    return 0;
}
