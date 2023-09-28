#ifndef STEP
#define STEP
#include <Arduino.h>
#include <AccelStepper.h>
#include <PWMServo.h>

class Step {
  AccelStepper step_2, step_3, step_4;
  PWMServo plug_t2, plug_t3, plug_t4;
  const float factor = 1.4902;
  bool plug_open = false;
  byte selector = 0;
  public: void init(){
    step_2 = AccelStepper(AccelStepper::DRIVER, stp_pin_t2, dir_pin_t2);
    step_3 = AccelStepper(AccelStepper::DRIVER, stp_pin_t3, dir_pin_t3);
    step_4 = AccelStepper(AccelStepper::DRIVER, stp_pin_t4, dir_pin_t4);
    step_2.setMaxSpeed(1000);
    step_3.setMaxSpeed(1000);
    step_4.setMaxSpeed(1000);
    digitalWrite(enb_pin_t2, HIGH); // Disable steppers
    digitalWrite(enb_pin_t3, HIGH); 
    digitalWrite(enb_pin_t4, HIGH); 
    plug_t2.attach(plug_pin_t2, 500, 2500);
    plug_t3.attach(plug_pin_t3, 500, 2500);
    plug_t4.attach(plug_pin_t4, 500, 2500);
  }
  public: void update(byte cmd, byte pwm){ // speed arg here #1
    if(cmd == 0){
      selector = 0;
      plug_t2.write(plug_closed_t2);
      plug_t3.write(plug_closed_t3);
      plug_t4.write(plug_closed_t4);
      digitalWrite(enb_pin_t2, HIGH); 
      digitalWrite(enb_pin_t3, HIGH); 
      digitalWrite(enb_pin_t4, HIGH); 
    }else if(cmd == 12){
      selector = 2;
      digitalWrite(enb_pin_t2, LOW); // ACTIVE LOW
      digitalWrite(enb_pin_t3, HIGH); 
      digitalWrite(enb_pin_t4, HIGH); 
    }else if(cmd == 13){
      selector = 3;
      digitalWrite(enb_pin_t2, HIGH); 
      digitalWrite(enb_pin_t3, LOW); // ACTIVE LOW
      digitalWrite(enb_pin_t4, HIGH); 
    }else if(cmd == 14){
      selector = 4;
      digitalWrite(enb_pin_t2, HIGH); 
      digitalWrite(enb_pin_t3, HIGH); 
      digitalWrite(enb_pin_t4, LOW); // ACTIVE LOW
    }
    if(selector == 2){
      step_2.setSpeed(pwm*factor);
    }else if(selector == 3){
      step_3.setSpeed(pwm*factor);
    }else if(selector == 4){
      step_4.setSpeed(pwm*factor);
    }
  }
  public: void run(byte pwm){
    plug_open = digitalRead(cmd_pin_6);
    if(selector == 2){
      step_2.runSpeed();
      if(plug_open) plug_t2.write(plug_open_t2);
      else          plug_t2.write(plug_closed_t2);
    }else if(selector == 3){
      step_3.runSpeed();
      if(plug_open) plug_t2.write(plug_open_t3);
      else          plug_t2.write(plug_closed_t3);
    }else if(selector == 4){
      step_4.runSpeed();
      if(plug_open) plug_t2.write(plug_open_t4);
      else          plug_t2.write(plug_closed_t4);
    }
  }
};

// #ifndef STEP
// #define STEP
// #include <Arduino.h>
// #include <AccelStepper.h>

// class Step {
//   AccelStepper stepper;
//   const float pla_speed_coefficient = 1.9065;
//   const int dir_input_pin = 36;
//   const int aux1_input_pin = 34; 
//   const int aux2_input_pin = 35;
//   const int stp_pin = 26;
//   const int dir_pin = 27;
//   const int enb_pin = 37;
//   byte speed, dir; // uint8_t
//   public: void init(){
//     pinMode(dir_input_pin, INPUT);
//     pinMode(aux1_input_pin, INPUT);
//     pinMode(aux2_input_pin, INPUT);
//     pinMode(stp_pin, OUTPUT);
//     pinMode(dir_pin, OUTPUT);
//     pinMode(enb_pin, OUTPUT);
//     stepper = AccelStepper(AccelStepper::DRIVER, stp_pin, dir_pin);
//     stepper.setMaxSpeed(1000);
//     stepper.setSpeed(0);
//     digitalWrite(dir_pin, LOW);
//     digitalWrite(enb_pin, LOW); // ACTIVE LOW
//   }
//   public: void update(byte cmd, byte pwm){ // speed arg here #1

//     stepper.setSpeed(speed*pla_speed_coefficient);//stepper.setSpeed(speed*speed_coefficient*(1-dir*2));
//     stepper.runSpeed();

//   }
// };




















    //stepper.setAcceleration(10);

    //delay(500);
    
    //start = micros();
    // Call to your function
    //speed = Get_PWM(speed_input_pin);
    //dir = digitalRead(dir_input_pin);
    //int test_speed = (1-dir*2)*speed;

    //Serial.println(test_speed);
    // Compute the time it took
    //end = micros();
    //delta = end - start;
    //Serial.println(delta);

    //Serial.println("hello");
    // delay(100);
    // digitalWrite(heat_pin, HIGH); //led_on(LED_BUILTIN);
    // delay(100);
    // digitalWrite(heat_pin, LOW); //led_off(LED_BUILTIN);
    // delay(100);

#endif