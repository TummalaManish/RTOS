## Thread Signals

###### Test Case: Runs a Master thread which in turn launch slave thread.

Slave thread receives different signals from the master and responds approximately.

Tests the following functionality.

* signal_on_bits()
* wait_for_signal_on_bits()

`OutPut:`
>Correct signal received before time-out.\
 Unexpected signal received.\
 Signal wait timed out.\
 Ending the test.\