# CradleEye 👶🛡️  
A Smart Infant Monitoring System
## 🍼 Introduction

**CradleEye** is an innovative smart monitoring system for infants that combines IoT and machine learning to assist parents in tracking their baby’s well-being. It monitors environmental conditions and detects specific baby cries to provide alerts when attention is needed.

## 🚀 The Problem

Infants cannot communicate their needs clearly. Parents often find it difficult to distinguish between different types of cries (hunger, discomfort, pain, etc.) and remain unaware of environmental changes like temperature drops or noise disturbances.

## 🦸 The Solution

CradleEye uses embedded hardware and intelligent algorithms to monitor the infant’s environment and behavior. Key features include:

- Cry Detection & Classification (e.g., hunger, pain, discomfort)
- Environment Monitoring (Temperature, Humidity, Noise)
- Real-Time Alerts via Push Notifications
- Data Logging for Long-Term Insights

## 🛠️ Technologies Used

- **IoT Hardware:** ESP8266, DHT11, Sound Sensor, Microphone
- **Machine Learning:** CRNN (Convolutional Recurrent Neural Network) for cry classification
- **Backend:** Python, Flask
- **Frontend:** Web interface (React planned)
- **Cloud:** Firebase / Blynk for real-time alerts

## 📑 Dataset

We are using baby cry audio datasets available from open repositories for training our ML model. One of the sources is:

- [https://www.kaggle.com/datasets/aniruth100/baby-cry-detection](https://www.kaggle.com/datasets/aniruth100/baby-cry-detection)

Additional datasets under consideration:

- https://data.mendeley.com/datasets/hbppd883sd/1  
- https://m.datatang.ai/dataset/998

