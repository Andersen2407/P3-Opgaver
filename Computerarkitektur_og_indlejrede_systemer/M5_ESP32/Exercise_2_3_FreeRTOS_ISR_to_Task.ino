// Define a pointer to the task handler (Points to a task/'thread')
TaskHandle_t xTHandler;

// Define a message queue handle
QueueHandle_t xQueue;

// Define a flag to indicate data availability
volatile bool dataAvailable = false;

// Interrupt function using fast ram
void IRAM_ATTR isrFunction() {
  // Notify the task that data is available
  vTaskNotifyGiveFromISR(xTHandler, NULL);

  int data = random(0, 100);  // Generate a random number between 0 and 99
  xQueueSend(xQueue, &data, portMAX_DELAY);
  dataAvailable = true;
}

void setup() {
  Serial.begin(115200);
  // Initialize the message queue
  xQueue = xQueueCreate(5, sizeof(char));
  // Create a task that will wait for notifications from the ISR
  //taskFunctions, name, stack-size, the passed parameters, priority, reference to task handler, xCoreID/The Core to run on
  xTaskCreatePinnedToCore(taskFunction, "Task", 10000, NULL, 1, &xTHandler, 0);

  // Attach the ISR to a specific interrupt
  // 0 = The left button
  attachInterrupt(digitalPinToInterrupt(0), isrFunction, RISING);
}

void loop() { /* This function is not used when using FreeRTOS*/}

void taskFunction(void* pvParameters) {
  while (1) {
    // Wait for a notification from the ISR
    //Empties the counter on exit, waits for the max amount of time
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    if (dataAvailable) {
      // Receive data from task1 through the queue
      int receivedData;
      if (xQueueReceive(xQueue, &receivedData, portMAX_DELAY) == pdTRUE) {
        // Process the received data
        Serial.print("Received ");
        Serial.print(receivedData);
        Serial.println(" from IRS");
      }

      // Reset the dataAvailable flag
      dataAvailable = false;
    }
  }
}