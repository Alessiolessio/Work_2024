#ifndef ENCODER_H
    #define ENCODER_H

    /**
     * @file encoder.c
     * @brief Implementation of the rotary encoder driver
     *
     * This file contains the implementation of the driver for the rotary encoder, 
     * which uses the PCNT peripheral to count pulses generated by the encoder. 
     * Callbacks are also registered to handle reach events defined by watchpoints.
     *
     * Authors:
     *          
     */
    
    /* Libraries */
    #include "sdkconfig.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "freertos/queue.h"
    #include "esp_log.h"
    #include "driver/pulse_cnt.h"
    #include "driver/gpio.h"
    #include "esp_sleep.h"

    /* Enum */
    typedef enum {
        ENC_LEFT = 0,
        ENC_RIGHT = 1
    } encoder_side_t;

    /* Macros */

    /* PCNT Limits */
    #define PCNT_HIGH_LIMIT 1500
    #define PCNT_LOW_LIMIT  -1500

    /* Right encoder defines */
    #define CHA_ENCODER_1R 15
    #define CHA_ENCODER_2R 14

    /* Left encoder defines */
    #define CHA_ENCODER_1L 18
    #define CHA_ENCODER_2L 19

    /* Macro functions */

    #define ENCODER_INPUT_A(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_1R : CHA_ENCODER_1L
    #define ENCODER_INPUT_B(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_2R : CHA_ENCODER_2L

    /* Functions prototypes */

    /**
     * @brief Get the handle of the selected encoder unit
     * 
     * This function returns the handle of the selected encoder unit based on the provided side.
     * 
     * @param encoder Encoder side (ENC_LEFT or ENC_RIGHT)
     * @return pcnt_unit_handle_t Handle of the selected encoder unit
     */
    pcnt_unit_handle_t encoder_side(encoder_side_t encoder);

    /**
     * @brief Initialize and configure an encoder unit
     * 
     * This function initializes and configures an encoder unit with specified parameters.
     * 
     * @param encoder Handle of the encoder unit to be configured
     * @param cha_encoder Flag indicating the channel A of the encoder
     */
   pcnt_unit_handle_t  init_encoder(encoder_side_t cha_encoder);

    /**
     * @brief Callback function when a watchpoint is reached
     * 
     * This function is called when a watchpoint is reached and handles event data.
     * 
     * @param unit Handle of the encoder unit
     * @param edata Event data for the watchpoint
     * @param user_ctx User context data (Queue handle)
     * @return bool True if high task wakeup is requested, false otherwise
     */
    bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx);

    /**
     * @brief Get the pulse count from the selected encoder unit
     * 
     * This function retrieves the pulse count from the selected encoder unit.
     * 
     * @param encoder Handle of the encoder unit to read from
     * @return float Pulse count from the encoder
     */
    float pulse_count(pcnt_unit_handle_t encoder);

#endif