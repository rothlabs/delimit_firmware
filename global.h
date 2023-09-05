#ifndef GLOBAL
#define GLOBAL

// Pin Assigment 
#define air_pin_t1  0 // heat
#define heat_pin_t2 1 
#define heat_pin_t3 2 
#define heat_pin_t4 3 

#define flow_pin_t1a 4 // H2O
#define flow_pin_t1b 5 // PVA
#define flow_pin_t1c 6 // PU Part A
#define flow_pin_t1d 7 // PU Part B

#define laser_pin_t5 8 // tool 5 - laser and fiber
#define fiber_pin_t5 9 

#define therm_pin_t2 14 // hotend thermistors
#define therm_pin_t3 15 
#define therm_pin_t4 16

#define dir_pin_t2  24 // tool 2 - extruder stepper
#define stp_pin_t2  25 
#define enb_pin_t2  26

#define dir_pin_t3 27 // tool 3 - extruder stepper
#define stp_pin_t3 28 
#define enb_pin_t3 29

#define dir_pin_t4 30 // tool 4 - extruder stepper
#define stp_pin_t4 31 
#define enb_pin_t4 32

#define cmd_pin_1 33 // command from grblhal
#define cmd_pin_2 34
#define cmd_pin_3 35
#define cmd_pin_4 36
#define cmd_pin_5 37
#define cmd_pin_6 38
#define pwm_pin   39

// Settings 
#define flow_off_t1a 45
#define flow_on_t1a 180
#define flow_off_t1b 45
#define flow_on_t1b 180
#define flow_off_t1c 45
#define flow_on_t1c 180
#define flow_off_t1d 45
#define flow_on_t1d 180

#endif