# Component description for SEGGER_RTT

SEGGER RTT can be configured with six different attributes that are as follows

1. RTT_UP_BUFFER_SIZE            : size of each up-buffer.
2. RTT_UP_BUFFER_COUNT           : Number of up buffers in the system.
3. RTT_DOWN_BUFFER_SIZE          : size of each down-buffer.
4. RTT_DOWN_BUFFER_COUNT         : number of down buffers in the system.
5. RTT_MAX_INTERRUPT_PRIO        : The highest priority that uses the RTT.
6. RTT_PRINTF_BUFFER_SIZE        : Size of the print buffer.

All the above mentioned configuration items have to be defined by the library user
if not a default configuration will be used and a warning will be thrown.