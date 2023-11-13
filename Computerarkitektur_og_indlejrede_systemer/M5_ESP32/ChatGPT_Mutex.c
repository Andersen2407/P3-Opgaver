// write c code which demonstrate an interrupt service routine signaling to a task using freertos and coding in c

SemaphoreHandle_t semaphore;

void IRAM_ATTR buttonISR() {
  // Notify the task that the button was pressed.
  xSemaphoreGiveFromISR(semaphore, NULL);
}

void taskFunction(void *pvParameters) {
  for (;;) {
    // Wait for the semaphore to be given from the ISR.
    if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
      // Perform task actions here.
      Serial.println("Button pressed!");
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Create a semaphore to signal the task.
  semaphore = xSemaphoreCreateBinary();

  // Initialize the button pin as an input.
  pinMode(0, INPUT_PULLUP);

  // Attach the ISR to the button pin.
  attachInterrupt(digitalPinToInterrupt(35), buttonISR, FALLING);

  // Create a task to handle the button press.
  xTaskCreatePinnedToCore(taskFunction, "ButtonTask", 10000, NULL, 1, NULL, 0);
}

void loop() {
}