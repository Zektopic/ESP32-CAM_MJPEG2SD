#include "esp_camera.h"
#include <Arduino.h>

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define LED_FLASH_PIN      4

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== ESP32-CAM HARDWARE & SENSOR DIAGNOSTIC ===");

  // Test flash LED
  pinMode(LED_FLASH_PIN, OUTPUT);
  Serial.println("Testing Flash LED on GPIO 4 (ON for 1 sec)...");
  digitalWrite(LED_FLASH_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_FLASH_PIN, LOW);
  Serial.println("Flash LED test complete.");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.grab_mode = CAMERA_GRAB_LATEST;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("esp_camera_init failed: 0x%x\n", err);
    return;
  }
  Serial.println("Camera init OK!");

  sensor_t* s = esp_camera_sensor_get();
  Serial.printf("Sensor PID: 0x%x\n", s->id.PID);

  // Test 1: Colorbar pattern
  Serial.println("\n--- TEST 1: Enabling Hardware Colorbar Generator ---");
  s->set_colorbar(s, 1);
  delay(500);
  camera_fb_t* fb = esp_camera_fb_get();
  if (fb) {
    Serial.printf("Colorbar frame captured: len=%u bytes, format=%d, width=%u, height=%u\n", fb->len, fb->format, fb->width, fb->height);
    // Print first 32 bytes of JPEG header
    Serial.print("JPEG bytes: ");
    for (int i = 0; i < min((size_t)32, fb->len); i++) Serial.printf("%02X ", fb->buf[i]);
    Serial.println();
    esp_camera_fb_return(fb);
  } else {
    Serial.println("Failed to get colorbar frame!");
  }

  // Test 2: Normal camera with Flash LED turned ON
  Serial.println("\n--- TEST 2: Normal sensor with Flash LED ON ---");
  s->set_colorbar(s, 0);
  s->set_brightness(s, 2);
  s->set_contrast(s, 0);
  s->set_saturation(s, 0);
  s->set_gainceiling(s, GAINCEILING_16X);
  s->set_gain_ctrl(s, 1);
  s->set_exposure_ctrl(s, 1);
  s->set_ae_level(s, 2); // maximum exposure

  digitalWrite(LED_FLASH_PIN, HIGH); // Flash LED ON
  delay(1000); // Allow sensor AGC/AEC to settle

  for (int f = 0; f < 5; f++) {
    fb = esp_camera_fb_get();
    if (fb) {
      Serial.printf("Frame %d (with flash LED): len=%u bytes\n", f + 1, fb->len);
      if (f == 4) {
        // Output raw JPEG to base64 or marker so we can inspect on host
        Serial.print("JPEG_START:");
        for (size_t i = 0; i < fb->len; i++) Serial.printf("%02x", fb->buf[i]);
        Serial.println(":JPEG_END");
      }
      esp_camera_fb_return(fb);
    }
    delay(200);
  }
  digitalWrite(LED_FLASH_PIN, LOW);
  Serial.println("Diagnostic complete!");
}

void loop() {
  delay(10000);
}
