/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432P401R
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_MSP432P401x
#define DeviceFamily_MSP432P401x
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  ============================= Display =============================
 */

#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>

#define Display_UARTBUFFERSIZE 1024
static char displayUARTBuffer[Display_UARTBUFFERSIZE];

DisplayUart_Object displayUartObject;

const DisplayUart_HWAttrs displayUartHWAttrs = {
    .uartIdx      = CONFIG_UART_0,
    .baudRate     = 9600,
    .mutexTimeout = (unsigned int)(-1),
    .strBuf       = displayUARTBuffer,
    .strBufLen    = Display_UARTBUFFERSIZE
};

const Display_Config Display_config[] = {
    /* Display_Type_UART */
    /* XDS110 UART */
    {
        .fxnTablePtr = &DisplayUartMin_fxnTable,
        .object      = &displayUartObject,
        .hwAttrs     = &displayUartHWAttrs
    },
};

const uint_least8_t Display_count = 1;


/*
 *  =============================== ADC ===============================
 */

#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCMSP432.h>

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <ti/devices/msp432p4xx/driverlib/ref_a.h>

#define CONFIG_ADC_COUNT 2

/*
 *  ======== adcMSP432Objects ========
 */
ADCMSP432_Object adcMSP432Objects[CONFIG_ADC_COUNT];

/*
 *  ======== adcMSP432HWAttrs ========
 */
const ADCMSP432_HWAttrsV1 adcMSP432HWAttrs[CONFIG_ADC_COUNT] = {
    /* PH_SENSOR */
    {
        .adcPin = ADCMSP432_P5_1_A4,
        .refVoltage = ADCMSP432_REF_VOLTAGE_VDD,
        .resolution = ADC_14BIT,
        .refExtValue = 3300000
    },
    /* HUMIDITY_SENSOR */
    {
        .adcPin = ADCMSP432_P5_0_A5,
        .refVoltage = ADCMSP432_REF_VOLTAGE_VDD,
        .resolution = ADC_14BIT,
        .refExtValue = 3300000
    },
};

/*
 *  ======== ADC_config ========
 */
const ADC_Config ADC_config[CONFIG_ADC_COUNT] = {
    /* PH_SENSOR */
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[PH_SENSOR],
        .hwAttrs = &adcMSP432HWAttrs[PH_SENSOR]
    },
    /* HUMIDITY_SENSOR */
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[HUMIDITY_SENSOR],
        .hwAttrs = &adcMSP432HWAttrs[HUMIDITY_SENSOR]
    },
};

const uint_least8_t ADC_count = CONFIG_ADC_COUNT;


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* MOTOR_1_A */
    GPIOMSP432_P4_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    /* MOTOR_1_B */
    GPIOMSP432_P4_1 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    /* MOTOR_2_A */
    GPIOMSP432_P4_2 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    /* MOTOR_2_B */
    GPIOMSP432_P4_3 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    /* MOTOR_3_A */
    GPIOMSP432_P4_4 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* MOTOR_3_B */
    GPIOMSP432_P4_5 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* MOTOR_4_A */
    GPIOMSP432_P4_6 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* MOTOR_4_B */
    GPIOMSP432_P4_7 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* MOTOR_nSLEEP_1 */
    GPIOMSP432_P6_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* MOTOR_nSLEEP_2 */
    GPIOMSP432_P6_1 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *
 *  NOTE: Unused callback entries can be omitted from the callbacks array to
 *  reduce memory usage by enabling callback table optimization
 *  (GPIO.optimizeCallbackTableSize = true)
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    /* MOTOR_1_A */
    NULL,
    /* MOTOR_1_B */
    NULL,
    /* MOTOR_2_A */
    NULL,
    /* MOTOR_2_B */
    NULL,
    /* MOTOR_3_A */
    NULL,
    /* MOTOR_3_B */
    NULL,
    /* MOTOR_4_A */
    NULL,
    /* MOTOR_4_B */
    NULL,
    /* MOTOR_nSLEEP_1 */
    NULL,
    /* MOTOR_nSLEEP_2 */
    NULL,
};

/*
 *  ======== GPIOMSP432_config ========
 */
const GPIOMSP432_Config GPIOMSP432_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = 10,
    .numberOfCallbacks = 10,
    .intPriority = (~0)
};


/*
 *  =============================== PWM ===============================
 */

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerMSP432.h>

/* include MSP432 driverlib definitions */
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/timer_a.h>

#define CONFIG_PWM_COUNT 7

/*
 *  ======== pwmMSP432Objects ========
 */
PWMTimerMSP432_Object pwmTimerMSP432Objects[CONFIG_PWM_COUNT];

/*
 *  ======== pwmMSP432HWAttrs ========
 */
const PWMTimerMSP432_HWAttrsV2 pwmTimerMSP432HWAttrs[CONFIG_PWM_COUNT] = {
    /* SERVO_0 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_4_TA0CCR4A, /* P2_4 */
    },
    /* SERVO_1 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_5_TA0CCR3A, /* P2_5 */
    },
    /* SERVO_2 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_6_TA0CCR2A, /* P2_6 */
    },
    /* PWM_MOTOR_0 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P3_0_TA1CCR3A, /* P3_0 */
    },
    /* PWM_MOTOR_1 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P3_5_TA0CCR1A, /* P3_5 */
    },
    /* PWM_MOTOR_2 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P3_6_TA1CCR2A, /* P3_6 */
    },
    /* PWM_MOTOR_3 */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P3_7_TA1CCR1A, /* P3_7 */
    },
};

/*
 *  ======== PWM_config ========
 */
const PWM_Config PWM_config[CONFIG_PWM_COUNT] = {
    /* SERVO_0 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[SERVO_0],
        .hwAttrs = &pwmTimerMSP432HWAttrs[SERVO_0]
    },
    /* SERVO_1 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[SERVO_1],
        .hwAttrs = &pwmTimerMSP432HWAttrs[SERVO_1]
    },
    /* SERVO_2 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[SERVO_2],
        .hwAttrs = &pwmTimerMSP432HWAttrs[SERVO_2]
    },
    /* PWM_MOTOR_0 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[PWM_MOTOR_0],
        .hwAttrs = &pwmTimerMSP432HWAttrs[PWM_MOTOR_0]
    },
    /* PWM_MOTOR_1 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[PWM_MOTOR_1],
        .hwAttrs = &pwmTimerMSP432HWAttrs[PWM_MOTOR_1]
    },
    /* PWM_MOTOR_2 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[PWM_MOTOR_2],
        .hwAttrs = &pwmTimerMSP432HWAttrs[PWM_MOTOR_2]
    },
    /* PWM_MOTOR_3 */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[PWM_MOTOR_3],
        .hwAttrs = &pwmTimerMSP432HWAttrs[PWM_MOTOR_3]
    },
};

const uint_least8_t PWM_count = CONFIG_PWM_COUNT;


/*
 *  =============================== Power ===============================
 */

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432.h>
extern void PowerMSP432_initPolicy(void);
extern void PowerMSP432_sleepPolicy(void);

const PowerMSP432_ConfigV1 PowerMSP432_config = {
    .policyInitFxn         = PowerMSP432_initPolicy,
    .policyFxn             = PowerMSP432_sleepPolicy,
    .initialPerfLevel      = 2,
    .enablePolicy          = true,
    .enablePerf            = true,
    .enableParking         = false,
    .resumeShutdownHookFxn = NULL,
    .customPerfLevels      = NULL,
    .numCustom             = 0,
    .useExtendedPerf       = false,
    .configurePinHFXT      = false,
    .HFXTFREQ              = 0,
    .bypassHFXT            = false,
    .configurePinLFXT      = false,
    .bypassLFXT            = false,
    .LFXTDRIVE             = 0,
    .enableInterruptsCS    = false,
    .priorityInterruptsCS  = (~0),
    .isrCS                 = NULL
};


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <ti/devices/msp432p4xx/driverlib/uart.h>

#define CONFIG_UART_COUNT 3

UARTMSP432_Object uartMSP432Objects[CONFIG_UART_COUNT];

static const UARTMSP432_BaudrateConfig uartMSP432Baudrates[] = {
    /* {baudrate, input clock, prescalar, UCBRFx, UCBRSx, oversampling} */
    { 9600, 3000000, 19, 8, 85, 1 },
    { 9600, 6000000, 39, 1, 0, 1 },
    { 9600, 12000000, 78, 2, 0, 1 },
    { 9600, 24000000, 156, 4, 0, 1 },
    { 9600, 32768, 3, 0, 146, 0 },
};

static unsigned char uartMSP432RingBuffer0[64];
static unsigned char uartMSP432RingBuffer1[128];
static unsigned char uartMSP432RingBuffer2[32];


static const UARTMSP432_HWAttrsV1 uartMSP432HWAttrs[CONFIG_UART_COUNT] = {
  {
    .baseAddr           = EUSCI_A2_BASE,
    .intNum             = INT_EUSCIA2,
    .intPriority        = (~0),
    .clockSource        = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    .bitOrder           = EUSCI_A_UART_LSB_FIRST,
    .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
                          sizeof(UARTMSP432_BaudrateConfig),
    .baudrateLUT        = uartMSP432Baudrates,
    .ringBufPtr         = uartMSP432RingBuffer0,
    .ringBufSize        = sizeof(uartMSP432RingBuffer0),
    .rxPin              = UARTMSP432_P3_2_UCA2RXD,
    .txPin              = UARTMSP432_P3_3_UCA2TXD,
    .errorFxn           = NULL
  },
  {
    .baseAddr           = EUSCI_A1_BASE,
    .intNum             = INT_EUSCIA1,
    .intPriority        = (~0),
    .clockSource        = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    .bitOrder           = EUSCI_A_UART_LSB_FIRST,
    .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
                          sizeof(UARTMSP432_BaudrateConfig),
    .baudrateLUT        = uartMSP432Baudrates,
    .ringBufPtr         = uartMSP432RingBuffer1,
    .ringBufSize        = sizeof(uartMSP432RingBuffer1),
    .rxPin              = UARTMSP432_P7_0_UCA1RXD,
    .txPin              = UARTMSP432_P7_1_UCA1TXD,
    .errorFxn           = NULL
  },
  {
    .baseAddr           = EUSCI_A0_BASE,
    .intNum             = INT_EUSCIA0,
    .intPriority        = (~0),
    .clockSource        = EUSCI_A_UART_CLOCKSOURCE_ACLK,
    .bitOrder           = EUSCI_A_UART_LSB_FIRST,
    .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
                          sizeof(UARTMSP432_BaudrateConfig),
    .baudrateLUT        = uartMSP432Baudrates,
    .ringBufPtr         = uartMSP432RingBuffer2,
    .ringBufSize        = sizeof(uartMSP432RingBuffer2),
    .rxPin              = UARTMSP432_P1_2_UCA0RXD,
    .txPin              = UARTMSP432_P1_3_UCA0TXD,
    .errorFxn           = NULL
  },
};

const UART_Config UART_config[CONFIG_UART_COUNT] = {
    {   /* BLUETOOTH */
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object      = &uartMSP432Objects[0],
        .hwAttrs     = &uartMSP432HWAttrs[0]
    },
    {   /* GPS */
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object      = &uartMSP432Objects[1],
        .hwAttrs     = &uartMSP432HWAttrs[1]
    },
    {   /* CONFIG_UART_0 */
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object      = &uartMSP432Objects[2],
        .hwAttrs     = &uartMSP432HWAttrs[2]
    },
};

const uint_least8_t UART_count = CONFIG_UART_COUNT;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    Board_initHook();
}
