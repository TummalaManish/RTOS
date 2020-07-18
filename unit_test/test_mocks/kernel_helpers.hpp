//
// Created by TUMMALA-MANISH on 18-07-2020.
//

#ifndef RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP
#define RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP

void vAssertCalled( unsigned long ulLine, const char * const pcFileName ){
    printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
    while(1);
}


extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                              StackType_t **ppxIdleTaskStackBuffer,
                                              uint32_t *pulIdleTaskStackSize);
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize){
    //TODO: No memory allocation has to be done for the idle task as the scheduler will not be started.
}

#endif //RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP
