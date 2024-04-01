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
   Project: ESP32 RTC Time
   Description: Setting and retrieving internal RTC time on ESP32
   Library: ESP32Time by fbiego https://github.com/fbiego/ESP32Time
   Board: ESP32
   External Modules: None
*/

#include <ESP32Time.h>

ESP32Time rtc;

void setup() {
  Serial.begin(115200);

  // set the time
  rtc.setTime(30, 24, 10, 1, 4, 2024);  // 1st Apr 2024 10:24:30
}

void loop() {
  // show the current time in the serial monitor
  Serial.println(rtc.getTimeDate(true));  //  (String) 10:24:38 Monday, April 1 2024
  delay(1000);
}
