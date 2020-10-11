/**
 * @author Alexander Grin
 * @copyright (C) 2020 Grin Development. All rights reserved.
 */

#include <stdlib.h>

#include "button_module.h"
#include "button_module_config.h"

/****************************** Common macros ********************************/
/** C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL                                (0)
#else
#define NULL                                ((void *) 0)
#endif
#endif

/*****************************************************************************/

typedef uint32_t timer_tiks_t;

typedef enum {
    STATE_RELEASE,
    STATE_PRESS
} state_t;

/**
 * @brief Button structure
 */
struct button {
    uint8_t id;
    button_lvl_t active_lvl;
    button_lvl_t lvl;
    state_t state;
    timer_tiks_t state_tiks;
    uint8_t press_counter;
    button_event_handler_fptr_t event_handler;
    void *args;
};

static inline void execute_event(button_handle_t handle, button_event_t event);

button_handle_t button_create(button_id_t id, button_lvl_t active_lvl,
        button_event_handler_fptr_t event_handler, void *args)
{
    button_handle_t rslt;

    if(event_handler == NULL ||
            (active_lvl != BUTTON_LVL_LOW && active_lvl != BUTTON_LVL_HIGH)) {
        rslt = NULL;
    }
    else {
        rslt = (button_handle_t ) malloc(sizeof(struct button));
        if(rslt) {
            rslt->id = id;
            rslt->active_lvl = active_lvl;
            rslt->lvl = !rslt->active_lvl;
            rslt->state = STATE_RELEASE;
            rslt->state_tiks = 0;
            rslt->press_counter = 0;
            rslt->event_handler = event_handler;
            rslt->args = args;
        }
    }

    return rslt;
}

button_err_t button_delete(button_handle_t *p_handle)
{
    button_err_t rslt = BUTTON_E_INVALID_ARG;

    if(p_handle) {
        if(*p_handle) {
            free(*p_handle);
            *p_handle = NULL;
            rslt = BUTTON_OK;
        }
    }

    return rslt;
}

button_err_t button_timer_tick_cb(button_handle_t handle)
{
    button_err_t rslt = BUTTON_OK;
    state_t new_state;

    if(handle == NULL) {
        rslt = BUTTON_E_INVALID_ARG;
        goto exit;
    }

    handle->state_tiks++;

    if(handle->state_tiks == BUTTON_BOUNCE_FILTER_TIKS) {
        if(handle->active_lvl == handle->lvl) {
            new_state = STATE_PRESS;
        }
        else {
            new_state = STATE_RELEASE;
        }

        if(handle->state != new_state) {
            handle->state = new_state;
            if(handle->state == STATE_PRESS) {
                handle->press_counter++;
                execute_event(handle, BUTTON_EVENT_PRESS);
            }
            else {
                execute_event(handle, BUTTON_EVENT_RELEASE);
            }
        }
    }

    if(handle->state == STATE_PRESS) {
        if(handle->state_tiks == BUTTON_HOLD_TIKS) {
            execute_event(handle, BUTTON_EVENT_HOLD);
        }
        if(handle->state_tiks == BUTTON_LONG_HOLD_TIKS) {
            execute_event(handle, BUTTON_EVENT_LONG_HOLD);
        }
        if(handle->state_tiks >= BUTTON_WAIT_TO_SERIAL_TIKS) {
            if(handle->state_tiks % BUTTON_SERIAL_PERIOD_TIKS == 0) {
                execute_event(handle, BUTTON_EVENT_SERIAL);
            }
        }
    }

    if (handle->state_tiks >= BUTTON_WAIT_TO_PRESS_TIKS) {
        if(handle->state == STATE_RELEASE) {
            switch (handle->press_counter) {
                case 1:
                    execute_event(handle, BUTTON_EVENT_SINGLE_PRESS);
                    break;
                case 2:
                    execute_event(handle, BUTTON_EVENT_DOUBLE_PRESS);
                    break;
                case 3:
                    execute_event(handle, BUTTON_EVENT_TRIPLE_PRESS);
                    break;
                case 4:
                    execute_event(handle, BUTTON_EVENT_QUADRUPLE_PRESS);
                    break;
                case 5:
                    execute_event(handle, BUTTON_EVENT_FIVEFOLD_PRESS);
                    break;
                default:
                    break;
            }
        }
        handle->press_counter = 0;
    }

exit:
    return rslt;
}

button_err_t button_isr_cb(button_handle_t handle, button_lvl_t lvl)
{
    button_err_t rslt;

    if(handle == NULL || (lvl != BUTTON_LVL_LOW && lvl != BUTTON_LVL_HIGH)) {
        rslt = BUTTON_E_INVALID_ARG;
    }
    else {
        handle->lvl = lvl;
        handle->state_tiks = 0;
        rslt = BUTTON_OK;
    }

    return rslt;
}

static inline void execute_event(button_handle_t handle, button_event_t event)
{
    handle->event_handler(handle->id, event,
            handle->args);
}
