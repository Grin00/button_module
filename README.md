# Button module
## Introduction
This package contains pure C button module. Module has bounce filter and helps detect different button's events.

## File information
The button module package includes:
* button_module.h - Module API
* button_module.c - Module API determination  
* button_module_config.h - Timing configuration 

## Integration details
* Integrate button_module.h, button_module.c and button_module_config.h in to the 
project.
* Include the button_module.h file in your code

## Usage guide
* Сreate button using "button_create" function
* Call "button_timer_tick_cb" function with frequency BUTTON_TIMER_RATE_HZ
* Call "button_isr_cb " function when the button level changed
* Handle events that occured in event_handler function

## Events
* BUTTON_EVENT_RELEASE - released
* BUTTON_EVENT_PRESS - pressed
    - To reliably trigger these events, a bounce filter is applied; you can configure it using BUTTON_BOUNCE_FILTER_TIKS
* BUTTON_EVENT_SINGLE_PRESS - pressed one times
* BUTTON_EVENT_DOUBLE_PRESS - pressed two times
* BUTTON_EVENT_TRIPLE_PRESS - pressed three times
* BUTTON_EVENT_QUADRUPLE_PRESS - pressed four times
* BUTTON_EVENT_FIVEFOLD_PRESS - pressed five times
    - The time between presses is configurable with BUTTON_WAIT_TO_PRESS_TIKS
* BUTTON_EVENT_HOLD - Withheld BUTTON_HOLD_TIKS time
* BUTTON_EVENT_LONG_HOLD - Withheld BUTTON_LONG_HOLD_TIKS time
* BUTTON_EVENT_SERIAL - Withheld BUTTON_WAIT_TO_SERIAL_TIKS time and occures with period BUTTON_SERIAL_PERIOD_TIKS

## Contributing
Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.
