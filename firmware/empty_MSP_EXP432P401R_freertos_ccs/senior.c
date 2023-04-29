/*
 *  ======== senior.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/ADC.h>
#include <ti/display/Display.h>
//#include <ti/drivers/TIMER.h>

/* Driver configuration */
#include "ti_drivers_config.h"
#include "inc/motors.h"
#include "inc/servo.h"
#include "inc/sensor.h"
#include "inc/hc_05.h"
#include "inc/gps.h"
/* Joystick Messages */
#define JOYSTICK_UP_MSG     "j-up\r"
#define JOYSTICK_DOWN_MSG   "j-down\r"
#define JOYSTICK_LEFT_MSG   "j-left\r"
#define JOYSTICK_RIGHT_MSG  "j-right\r"
#define JOYSTICK_BUTTON_MSG "j-button\r"
/* Button Messages */
#define BUTTON_UP_MSG       "b-up\r\n"
#define BUTTON_DOWN_MSG     "b-down\r\n"
#define BUTTON_LEFT_MSG     "b-left\r\n"
#define BUTTON_RIGHT_MSG    "b-right\r\n"

/* Global objects */


#ifdef MOTOR_TYPE_DC
motor_t motor_0 = {.a = MOTOR_1_A, .b = MOTOR_1_B};  // R1
motor_t motor_1 = {.a = MOTOR_2_A, .b = MOTOR_2_B};  // R2
motor_t motor_2 = {.a = MOTOR_3_A, .b = MOTOR_3_B};  // L1
motor_t motor_3 = {.a = MOTOR_4_A, .b = MOTOR_4_B};  // L2

motors_t right_side = {.motor_0 = &motor_0, .motor_1 = &motor_1, .sleep = MOTOR_nSLEEP_1, .state = NONE};
motors_t left_side = {.motor_0 = &motor_2, .motor_1 = &motor_3, .sleep = MOTOR_nSLEEP_2, .state = NONE};
#else
motor_t motor_0 = {.duty = STOP, .pwm = PWM_MOTOR_0, .handle = NULL};
motor_t motor_1 = {.duty = STOP, .pwm = PWM_MOTOR_1, .handle = NULL};
motor_t motor_2 = {.duty = STOP, .pwm = PWM_MOTOR_2, .handle = NULL};
motor_t motor_3 = {.duty = STOP, .pwm = PWM_MOTOR_3, .handle = NULL};

motors_t right_side = {.motor_1 = &motor_0, .motor_2 = &motor_1};
motors_t left_side = {.motor_1 = &motor_2, .motor_2 = &motor_3};
#endif

servo_t servo_0 = {.duty = SERVO_MIN, .pwm = SERVO_0, .handle = NULL};
servo_t servo_1 = {.duty = SERVO_MIN, .pwm = SERVO_1, .handle = NULL};
servo_t servo_2 = {.duty = SERVO_MIN, .pwm = SERVO_2, .handle = NULL};

arm_t robotic_arm = {.joint_0 = &servo_0, .joint_1 = &servo_1, .joint_2 = &servo_2};

bluetooth_t hc_05 = {.uart = BLUETOOTH,.handle = NULL, .buffer = "NONE"};

gps_t gps = {.uart = GPS,.handle = NULL, .buffer = "NONE"};


sensor_t ph_sensor = {.sensor = PH_SENSOR,.adc_avg = 0, .adc_value = 0,.adc_handle = NULL};
sensor_t humidity_sensor = {.sensor = HUMIDITY_SENSOR, .adc_avg = 0, .adc_value = 0, .adc_handle = NULL};


/*
 *  ======== mainThread ========
 */

bool isSubstring(char *str, char *substr){
    int i;
    int len = strlen(str);
    int len2 = strlen(substr);
    for(i = 0; i < len; i++){
        if(str[i] == substr[0]){
            int j;
            int temp = i;
            for(j = 0; j < len2; j++){
                if(substr[j] == str[temp++])
                    continue;
                else{
                    break;
                }
            }
            if(temp - i == strlen(substr)){
                return true;
            }
        }
    }
    return false;
}

void *mainThread(void *arg0)
{
#ifdef MOTOR_TYPE_DC
    motors_init(&right_side);
    motors_init(&left_side);
#else
    motors_init(&left_side, &right_side);
#endif

    arm_init(&robotic_arm);
    hc_05_init(&hc_05);
    gps_init(&gps);
    sensor_init(&ph_sensor);
    sensor_init(&humidity_sensor);

    arm_set_duty_all(&robotic_arm, SERVO_AVERAGE);

    Display_init();
    Display_Params displayParams;
    Display_Handle displayHandle;
    Display_Params_init(&displayParams);
    displayParams.lineClearMode = DISPLAY_CLEAR_BOTH;

    displayHandle = Display_open(Display_Type_UART,&displayParams);

    if(displayHandle == NULL){
        Display_printf(displayHandle, 0,0, "Display has not been successfully setup!\n");
        while(1);
    }
    else{
        Display_printf(displayHandle, 0,0, "Display has been successfully setup!\n");
    }
#ifdef MOTOR_TYPE_DC
    motors_enable(&left_side);
    motors_enable(&right_side);
#else
    motors_pwm_start(&left_side, &right_side);
#endif
    arm_start(&robotic_arm);
    while(1){

        hc_05_read(&hc_05);
        Display_printf(displayHandle, 0,0, "%s", hc_05.buffer);
#ifdef MOTOR_TYPE_DC
        if(isSubstring(hc_05.buffer,"j-up")){
            Display_printf(displayHandle, 0,0, "J-FORWARD\n");
            motors_forward(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-button")){
            Display_printf(displayHandle, 0,0, "J-BACKWARD\n");
            motors_backward(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-left")){
            Display_printf(displayHandle, 0,0, "J-LEFT\n");
            motors_left(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-right")){
            Display_printf(displayHandle, 0,0, "J-RIGHT\n");
            motors_right(&left_side, &right_side);
        }
#else
        /* Note: Motors R1 and R2 have flipped polarity */
        /* Todo: change function calls to same as above */

        if(isSubstring(hc_05.buffer,"j-up")){
            Display_printf(displayHandle, 0,0, "J-FORWARD\n");
            motors_right(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-button")){
            Display_printf(displayHandle, 0,0, "J-BACKWARD\n");
            motors_left(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-left")){
            Display_printf(displayHandle, 0,0, "J-LEFT\n");
            motors_backward(&left_side, &right_side);
        }
        else if(isSubstring(hc_05.buffer,"j-right")){
            Display_printf(displayHandle, 0,0, "J-RIGHT\n");
            motors_forward(&left_side, &right_side);
        }
#endif
        else if(isSubstring(hc_05.buffer,"b-up")){
            Display_printf(displayHandle, 0,0, "B-UP\n");
            if(robotic_arm.joint_1->duty >= SERVO_MAX && robotic_arm.joint_2->duty <= SERVO_MIN){
                servo_set_duty(robotic_arm.joint_1, SERVO_MAX);
                servo_set_duty(robotic_arm.joint_2, SERVO_MIN);
            }
            else{
                robotic_arm.joint_1->duty += 2400;
                robotic_arm.joint_2->duty -= 2400;
                arm_set_duty(&robotic_arm, robotic_arm.joint_1->duty, 2);
                arm_set_duty(&robotic_arm, robotic_arm.joint_2->duty, 3);
            }

        }
        else if(isSubstring(hc_05.buffer,"b-down")){
            Display_printf(displayHandle, 0,0, "B-DOWN\n");

            if(robotic_arm.joint_1->duty <= SERVO_MIN && robotic_arm.joint_2->duty >= SERVO_MAX){
                servo_set_duty(robotic_arm.joint_1, SERVO_MIN);
                servo_set_duty(robotic_arm.joint_2, SERVO_MAX);
            }
            else{
                robotic_arm.joint_1->duty -= 2400;
                robotic_arm.joint_2->duty += 2400;
                arm_set_duty(&robotic_arm, robotic_arm.joint_1->duty, 2);
                arm_set_duty(&robotic_arm, robotic_arm.joint_2->duty, 3);
            }
        }
        else if(isSubstring(hc_05.buffer,"b-right")){
            Display_printf(displayHandle, 0,0, "B-RIGHT\n");
            if(robotic_arm.joint_0->duty <= SERVO_MIN){
                servo_set_duty(robotic_arm.joint_0, SERVO_MIN);
            }
            else{
                robotic_arm.joint_0->duty -= 2400;
                arm_set_duty(&robotic_arm, robotic_arm.joint_0->duty, 1);
            }
        }
        else if(isSubstring(hc_05.buffer,"b-left")){
            Display_printf(displayHandle, 0,0, "B-LEFT\n");
            if(robotic_arm.joint_0->duty >= SERVO_MAX){
                servo_set_duty(robotic_arm.joint_0, SERVO_MAX);
            }
            else{
                robotic_arm.joint_0->duty += 2400;
                arm_set_duty(&robotic_arm, robotic_arm.joint_0->duty, 1);
            }
        }
        else{
            Display_printf(displayHandle, 0,0, "STOP\n");
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
        motors_stop(&left_side, &right_side);
    }
}
