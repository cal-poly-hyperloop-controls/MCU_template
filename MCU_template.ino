#include <ChRt.h>
#include <FlexCAN_T4.h>

#ifndef __IMXRT1062__
  #error "This sketch should be compiled for Teensy 4.0"
#endif


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;

//------------------------------------------------------------------------------
//Helper functions

//------------------------------------------------------------------------------

// Thread 1: responsible for calculating RPM and distance
// priority +1
static THD_WORKING_AREA(waThread1, 256);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  while(true){
  
  }
}

//------------------------------------------------------------------------------
// Thread 2: send data through canbus
// priority +2
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
  (void)arg;
  Serial.println("Thread 2 Initialized");
  while (true) {

    //Send CAN data
    
    chThdSleepMilliseconds(50);
  }
}

//------------------------------------------------------------------------------
// Thread 3: recieve messages through canbus
// priority +3
static THD_WORKING_AREA(waThread3, 64);
static THD_FUNCTION(Thread3, arg) {
  (void)arg;

  Serial.println("Thread 3 Initialized");
  while (true) {
    
    
    chThdSleepMilliseconds(50);
  }
}



//SETUP THREADS------------------------------------------------------------------------------
void chStartup() {
  // Schedule thread 3
  //priority +3
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO+3, Thread3, NULL);

  // Schedule thread 2
  //priority +2
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO+2, Thread2, NULL);

  // Schedule thread 1
  //priority +1
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);
}

void setup() {

  // Wait for USB Serial.
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("initializing...");

  //Init CAN
  can1.begin();
  can1.setBaudRate(250000);

  Serial.println("initializing RTOS..."); 
  
  // Initialize and start ChibiOS.
  chBegin(chStartup);
  // chBegin() resets stacks and should never return.
  while (true) {}  
}

void loop() {}
