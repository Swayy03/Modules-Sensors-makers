/*
   MIT License

  Copyright (c) 2024 Felix Biego

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ______________  _____
  ___  __/___  /_ ___(_)_____ _______ _______
  __  /_  __  __ \__  / _  _ \__  __ `/_  __ \
  _  __/  _  /_/ /_  /  /  __/_  /_/ / / /_/ /
  /_/     /_.___/ /_/   \___/ _\__, /  \____/
                              /____/

*/


/*
   Project: ESP32 Smartwatch
   Description: Simple smartwatch implementation with ESP32. Includes BLE data sync with Chronos App
   Library: ChronosESP32 by fbiego https://github.com/fbiego/chronos-esp32
   Library Dependencies: ESP32Time by fbiego, NimBLE-Arduino by h2zero
   Board: ESP32
   External Modules: None
   App: Chronos by fbiego on Playstore (Android only)
*/

#include <ChronosESP32.h>

ChronosESP32 watch("ESP32 Watch"); // set the bluetooth name

void connectionCallback(bool state)
{
  Serial.print("Connection state: ");
  Serial.println(state ? "Connected" : "Disconnected");
}

void notificationCallback(Notification notification)
{
  // you will need to setup notifications in the Chronos app in order to receive them,
  // you can also do a quick test using the Notification test feature
  Serial.print("Notification received at ");
  Serial.println(notification.time);
  Serial.print("From: ");
  Serial.print(notification.app);
  Serial.print("\tIcon: ");
  Serial.println(notification.icon);
  Serial.println(notification.message);
}

void ringerCallback(String caller, bool state)
{
  if (state)
  {
    Serial.print("Ringer: Incoming call from ");
    Serial.println(caller);
  }
  else
  {
    Serial.println("Ringer dismissed");
  }
}

void configCallback(Config config, uint32_t a, uint32_t b)
{
  switch (config)
  {
    case CF_FIND:
      Serial.println("Find request");
      break;
    case CF_CAMERA:
      Serial.print("Camera: ");
      Serial.println(b ? "Active" : "Inactive");
      break;
    case CF_APP:
      Serial.print("Chronos App; Code: ");
      Serial.print(a); // int code = watch.getAppCode();
      Serial.print(" Version: ");
      Serial.println(watch.getAppVersion());
      break;
    case CF_WEATHER:
      if (a)
      {
        // if a == 1, high & low temperature values might not yet be updated
        if (a == 2)
        {
          Serial.println("Weather received");
          int n = watch.getWeatherCount();
          String updateTime = watch.getWeatherTime();
          Serial.print("Weather Count: ");
          Serial.print(n);
          Serial.print("\tUpdated at: ");
          Serial.println(updateTime);

          for (int i = 0; i < n; i++)
          {
            // iterate through weather forecast, index 0 is today, 1 tomorrow...etc
            Weather w = watch.getWeatherAt(i);
            Serial.print("Day:"); // day of the week (0 - 6)
            Serial.print(w.day);
            Serial.print("\tIcon:");
            Serial.print(w.icon);
            Serial.print("\t");
            Serial.print(w.temp);
            Serial.print("°C");
            Serial.print("\tHigh:");
            Serial.print(w.high);
            Serial.print("°C");
            Serial.print("\tLow:");
            Serial.print(w.low);
            Serial.println("°C");
          }
        }
      }
      if (b)
      {
        Serial.print("City name: ");
        String city = watch.getWeatherCity(); //
        Serial.print(city);
      }
      Serial.println();
      break;
  }
}


void setup()
{
  Serial.begin(115200);

  // set the callbacks before calling begin funtion
  watch.setConnectionCallback(connectionCallback);
  watch.setNotificationCallback(notificationCallback);
  watch.setRingerCallback(ringerCallback);
  watch.setConfigurationCallback(configCallback);

  watch.begin(); // initializes the BLE
  // go to Chronos app > Watches tab > Watches button > Pair New Devices > Search > Select your board
  // you only need to do it once. To disconnect, click on the rotating icon (Top Right)

  Serial.println(watch.getAddress()); // mac address, call after begin()

  watch.setBattery(80); // set the battery level, will be synced to the app
}

void loop()
{
  watch.loop(); // handles internal routine functions

  String time = watch.getHourC() + watch.getTime(":%M ") + watch.getAmPmC();
  Serial.println(time);
  delay(5000);
}
