#include <krnl.h>

const int STKSZ = 200;
char stak1[STKSZ], stak2[STKSZ];

struct k_t *pt1,  // pointer to hold reference
  *pt2;           // to taskdescriptor for t1 and t2

void t1(void) {
  while (1) {
    DI();
    k_sleep(100);
    digitalWrite(13, !digitalRead(13));
    EI();
  }
}

void t2() {
  unsigned int Counter = 0;
  unsigned long StartTime;

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

  // init krnl so you can create 2 tasks, no semaphores and no message queues
  k_init(2, 0, 0);
  pt1 = k_crt_task(t1, 11, stak1, STKSZ);
  pt2 = k_crt_task(t2, 11, stak2, STKSZ);

  k_start();  // start kernel with tick speed 1 milli seconds
}

void loop() {}