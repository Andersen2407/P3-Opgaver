#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static QueueHandle_t msgQ;
static const uint8_t msgQ_length = 10;

SemaphoreHandle_t semaphore;

void IRAM_ATTR buttonISR() {
  xSemaphoreGiveFromISR(semaphore, NULL);  // Signal the task from the ISR
}

void setup() {
  // Setup baud
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  semaphore = xSemaphoreCreateBinary(); // Mutex

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  msgQ = xQueueCreate(msgQ_length, sizeof(int));

  if (semaphore != NULL) {
    // Attach the ISR to the button pin.
    attachInterrupt(digitalPinToInterrupt(0), buttonISR, RISING);

    // Create a task to handle the button press.
    xTaskCreatePinnedToCore(ISRevent, "ISRdemo", 1024, NULL, 1, NULL, 1);

    xTaskCreatePinnedToCore(incrementer, "incrementer", 1024, NULL, 1, NULL, app_cpu);
  } else {
    Serial.println("Semaphore creation failed!");
  }
}


void ISRevent(void *pvParameters) {
  int RandomInt;

  while (1) {
    if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
      // Send random value to queue from 122 - 123.
      RandomInt = random(122, 125);

      if (xQueueSend(msgQ, (void *)&RandomInt, 10) != pdTRUE) {
        Serial.println("Queue is full!");
      }
    }
  }
}


void incrementer(void *Params) {
  int QItem;
  int LocalCounter;

  while (1) {
    if (xQueueReceive(msgQ, (void *)&QItem, 0) == pdTRUE) {
      // Check if the value is 123
      if ((int)QItem == 123) {
        LocalCounter++;
        Serial.println(QItem);
      } else {
        Serial.println("---");
      }
    } else {
      Serial.println("No messages in queue!");
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


void loop() {}
