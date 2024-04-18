#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define LED_PIN 15
#define NUM_LEDS 36
#define sensor 36

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

volatile bool interruptTriggered = false;

void IRAM_ATTR handleInterrupt()
{
    atualiza_tempo();
}

void setup()
{
    pinMode(sensor, INPUT);
    attachInterrupt(sensor, handleInterrupt, FALLING);

    strip.begin();
    strip.show(); // Initialize all pixels to off
}

void atualiza_tempo()
{
}

void loop()
{
    if (interruptTriggered)
    {
        int analogValue = analogRead(sensor);
        if (analogValue == 0)
        {
            // Turn on the LEDs in a sequence
            for (int i = 0; i < NUM_LEDS; i++)
            {
                strip.setPixelColor(i, strip.Color(255, 0, 0)); // Set color to red
                strip.show();
                delay(100);
                strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off the LED
                strip.show();
            }
        }
        interruptTriggered = false;
    }
}