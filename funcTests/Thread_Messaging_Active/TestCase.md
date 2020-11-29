## Thread Messaging

###### Test Case: Runs a Master thread which in turn launch slave thread.

Tests the following functionality.

* send_value_with_over_write()
* send_value_with_no_over_write()
* wait_for_value()

`OutPut:`
>Expected failure as there is a value waiting to be read\
 Correct value is received in time: f0ff0fff\
 Expected success as there is no value waiting to be read\
 Correct value is received in time: f0ff0fff\
 In-correct value is received in time: f0ff1001\
 Message wait time timed out\
 Ending the test.\