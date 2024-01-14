// Define a mutex handle
SemaphoreHandle_t xMutex;

// Define a message queue handle
QueueHandle_t xQueue;

void setup() {
 Serial.begin(115200);
 // Initialize the mutex (semaphor with 1 key only)
 xMutex = xSemaphoreCreateMutex();

 // Initialize the message queue of 10 "items" each containing a char
 xQueue = xQueueCreate(10, sizeof(char));

 // Check if the mutex and queue were created successfully
 if (xMutex != NULL && xQueue != NULL) {
   // Create tasks
   xTaskCreatePinnedToCore(task1, "Task1", 4096, NULL, 1, NULL, 0);
   xTaskCreatePinnedToCore(task2, "Task2", 4096, NULL, 1, NULL, 0);
 } else {
   Serial.println("Mutex or Queue creation failed!");
   while (1);  // Handle error if creation fails
 }
}

void loop() {} // This function is not used when using FreeRTOS

void task1(void* pvParameters) {
 while (1) {
   // Generate some data
   int data = random(0, 100); // Generate a random number between 0 and 99

   Serial.println("(Task1) Acquiring mutex!");
   if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
     Serial.print("(Task1) Sending ");
     Serial.print(data);
     Serial.println(" to Task 2");
     // Send data to task2 through the queue
     xQueueSend(xQueue, &data, portMAX_DELAY);


     Serial.println("(Task1) Releasing mutex!\n");
     xSemaphoreGive(xMutex);
     vTaskDelay(pdMS_TO_TICKS(10));
   }
   // Delay for some time before sending the next message
   vTaskDelay(pdMS_TO_TICKS(1000));
 }
}

void task2(void* pvParameters) {
 while (1) {
   // Receive data from task1 through the queue
   int receivedData;
   while (xQueueReceive(xQueue, &receivedData, pdMS_TO_TICKS(1000)) == pdTRUE) {
     Serial.print("(Task2) Received ");
     Serial.print(receivedData);
     Serial.println(" from Task 1");
   }
   Serial.println("\n");
   // Delay for some time before receiving the next message
   vTaskDelay(pdMS_TO_TICKS(5000));
 }
}

// 1. We create a message queue (‘xQueue’) with a capacity for one message, but this can be adjusted as needed.
// 2. In the ISR (‘vISRHandler’), we send a 32-bit data value (in this case the value 42) to the message queue using ‘xQueueSendFromISR’.
// 3. The task (‘vTaskFunction’) waits for data to be received from the queue using ‘xQueueReceive’. When data is received, it processes the received data.
// 4. The main function initializes the message queue, creates the task and simulates the ISR signaling the task with data.

// This example demonstrates how to use a message queue to communicate between an ISR and a task in FreeRTOS.