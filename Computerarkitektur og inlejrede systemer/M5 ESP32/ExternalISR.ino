// Create an ISR that is triggered by a button press. Print every time the ISR happens.
// This can only be done in Freertos with a semaphore and not only by an external interrupt.

SemaphoreHandle_t semaphore;

void IRAM_ATTR buttonISR() {
  xSemaphoreGiveFromISR(semaphore, NULL);  // Signal the task from the ISR
}

void setup() {
  Serial.begin(115200);

  // Initialize the button pin as an input.
  pinMode(0, INPUT_PULLUP);

  // Create a semaphore to synchronize with the ISR.
  semaphore = xSemaphoreCreateBinary();

  // Check if the OS has created the semaphore.
  if (semaphore != NULL) {
    // Attach the ISR to the button pin.
    attachInterrupt(digitalPinToInterrupt(0), buttonISR, RISING);

    // Create a task to handle the button press.
    xTaskCreatePinnedToCore(main, "ISRdemo", 10000, NULL, 1, NULL, 0);
  } else {
    Serial.println("Semaphore creation failed!");
  }
}

void ISRevent (void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
      Serial.println("Button Pressed!");
    }
  }
}

void loop() {
  Serial.println("Main loop");
  vTaskDelay(1000);
}