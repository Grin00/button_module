/**
 * @author Alexander Grin
 * @copyright (C) 2020 Grin Development. All rights reserved.
 */

#ifndef BUTTON_MODULE_CONFIG_H
#define BUTTON_MODULE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUTTON_TIMER_RATE_HZ            (100)
#define BUTTON_TIMER_RATE_MS            (1000 / BUTTON_TIMER_RATE_HZ)

#define BUTTON_BOUNCE_FILTER_TIKS       (50 / BUTTON_TIMER_RATE_MS)
#define BUTTON_WAIT_TO_PRESS_TIKS       (500 / BUTTON_TIMER_RATE_MS)
#define BUTTON_HOLD_TIKS                (1000 / BUTTON_TIMER_RATE_MS)
#define BUTTON_LONG_HOLD_TIKS           (50000 / BUTTON_TIMER_RATE_MS)
#define BUTTON_WAIT_TO_SERIAL_TIKS      (3000 / BUTTON_TIMER_RATE_MS)
#define BUTTON_SERIAL_PERIOD_TIKS       (100 / BUTTON_TIMER_RATE_MS)

#ifdef __cplusplus
}
#endif

#endif//!BUTTON_MODULE_CONFIG_H
