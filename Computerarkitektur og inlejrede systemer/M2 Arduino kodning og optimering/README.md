**Alle opgaver har 2 filer (program.c and program.S)**
- program.S can be seen in the tasks below, where as program.c always contains the follwing:

extern "C" {
    void myInit();
    void myLoop();
}
void setup() {
    myInit();
}
void loop() {
    myLoop();
}

- They are both placed on the Arduino project folder!