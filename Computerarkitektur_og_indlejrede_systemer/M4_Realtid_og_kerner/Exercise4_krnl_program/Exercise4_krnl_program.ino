#include <krnl.h>

const int STKSZ = 200;
char stak1[STKSZ], stak2[STKSZ];

struct k_t *pt1, *pt2;  // pointer to hold reference to taskdescriptor for t1 and t2

void t1(void) {
  while (1) {
    DI();                       // Disable interrupts
    k_sleep(100);               // Put task to sleep mode
    digitalWrite(13, !digitalRead(13)); // Flip LED output
    EI();                       // Enable interrupts
  }
}

void t2() {
  unsigned int Counter = 0;
  unsigned long StartTime;

  // The task counts the amount of prints and how long they took. Here k_sleep makes the task take 400 ticks on the cpu
  // it reserves this due to non-preemptive scheduling
  while (1) {
    DI();
    StartTime = millis();
    k_sleep(400);
    Serial.print(Counter);
    Serial.print(" took (miliseconds): ");
    Serial.println(millis()-StartTime);
    Counter++;
    EI();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  // initialize kernel so you can create 2 tasks, 0 semaphores and 0 message queues
  k_init(2, 0, 0);

                  // Method which task will use
                      // Priority
                           // Stack the task will use
                                  // Stack size
  pt1 = k_crt_task(t1, 11, stak1, STKSZ);
  pt2 = k_crt_task(t2, 11, stak2, STKSZ);

  k_start();  // start kernel with tick speed 1 milli seconds
}

void loop() {}