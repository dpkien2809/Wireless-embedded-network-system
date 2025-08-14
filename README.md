# Meteorological Observations Using ESP32

## 📌 Overview
This project is a **Wireless Embedded Network System** for meteorological observation.  
It uses **ESP32** and **BME280** sensors to collect environmental data (temperature, humidity, atmospheric pressure) and apply **Machine Learning** to forecast local weather conditions.

The system integrates:
- **Embedded device** for data collection.
- **Cloud server** for storage and processing.
- **Mobile & Web interfaces** for monitoring and management.

## 🛠 Tools & Technologies
- **Arduino IDE** – Programming and flashing ESP32.
- **Visual Studio** – Building C-based server and cloud integration.
- **Android Studio** – Mobile UI for device management.
- **Google Colab** – Training ML models.
- **Azure App Service** – Hosting online server.
- **SQL Database** – Data storage.

## 📡 System Design
- **Sensor**: BME280 (temperature, humidity, pressure)
- **Embedded Device**: ESP32 with SPIFFS web server
- **Machine Learning**:
  - Models tested: Decision Tree, SVM, Random Forest
  - Dataset: 26,398 samples (6 weather labels)
  - Final choice: **Decision Tree** for its stability and lightweight performance.
- **Servers**:
  - Local web server (HTML, JS)
  - Online Azure web server (API + SQL database)
- **UI**:
  - Web: Real-time data visualization
  - Mobile: Device status & weather forecast

## 🚀 Deployment
- **Placement**: Device mounted outdoors, 32m above ground level.
- **Functions**:
  - Monitor environmental parameters in real time.
  - Forecast local weather conditions.
  - Track device status (online/offline) and manage multiple devices.

## 📈 Results & Conclusion
- Achieved objectives of a functional weather station.
- Successfully integrated embedded devices, cloud connectivity, and ML-based forecasting.
- **Future work**:
  - Add more environmental sensors.
  - Enhance user interfaces.
  - Improve server features for better device management.

## 📚 References
- [ESP32 Web Server Charts](https://randomnerdtutorials.com/esp32-esp8266-plot-chart-web-server/)
- [scikit-learn Documentation](https://scikit-learn.org/)
- [Android Developer Docs](https://developer.android.com/docs)
- [Microsoft Azure Docs](https://learn.microsoft.com/en-us/docs/)
- [Arduino Documentation](https://docs.arduino.cc/)

---
