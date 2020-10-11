/**
 * @author Alexander Grin
 * @copyright (C) 2020 Grin Development. All rights reserved.
 */

#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************* C types headers *****************************/

#include <stdint.h>

/**
 * @brief Button error code
 */
typedef enum {
    BUTTON_OK = 0,
    BUTTON_E_FAILED = -1,
    BUTTON_E_INVALID_ARG = -2
} button_err_t;

/**
 * @brief Button event
 */
typedef enum {
    BUTTON_EVENT_RELEASE,
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_SINGLE_PRESS,
    BUTTON_EVENT_DOUBLE_PRESS,
    BUTTON_EVENT_TRIPLE_PRESS,
    BUTTON_EVENT_QUADRUPLE_PRESS,
    BUTTON_EVENT_FIVEFOLD_PRESS,
    BUTTON_EVENT_HOLD,
    BUTTON_EVENT_LONG_HOLD,
    BUTTON_EVENT_SERIAL
} button_event_t;

typedef uint8_t button_id_t;

typedef enum {
    BUTTON_LVL_LOW,
    BUTTON_LVL_HIGH
} button_lvl_t;

/**
 * @brief Function pointer to button event handler
 *
 * @param id - button ID
 * @param event - event
 * @param args - pointer to the arguments
 */
typedef void (*button_event_handler_fptr_t)(button_id_t id,
        button_event_t event, void *args);

/**
 * @brief Button handle
 */
typedef struct button *button_handle_t;

/**
 * @brief Create button
 *
 * @param id - button ID
 * @param active_lvl - button active level
 * @param event_handler - button event handler
 * @param args - pointer to the arguments for event handler
 * @return
 *      - button object - success
 *      - NULL - memory allocation failed or invalid argument
 */
button_handle_t button_create(button_id_t id, button_lvl_t active_lvl,
        button_event_handler_fptr_t event_handler, void *args);

/**
 * @brief Delete button
 *
 * @param p_handle - pointer to button handle
 * @return
 *      - BUTTON_OK - success
 *      - BUTTON_E_INVALID_ARG - invalid argument
 */
button_err_t button_delete(button_handle_t *p_handle);

/**
 * @brief Button timer tick callback
 * @param handle - button handle
 * @return
 *      - BUTTON_OK - success
 *      - BUTTON_E_INVALID_ARG - invalid argument
 */
button_err_t button_timer_tick_cb(button_handle_t handle);

/**
 * @brief Button interrupt service callback
 *
 * @param handle - button handle
 * @param lvl - button level
 * @return
 *      - BUTTON_OK - success
 *      - BUTTON_E_INVALID_ARG - invalid argument
 */
button_err_t button_isr_cb(button_handle_t handle, button_lvl_t lvl);

#ifdef __cplusplus
}
#endif

#endif//!BUTTON_MODULE_H
