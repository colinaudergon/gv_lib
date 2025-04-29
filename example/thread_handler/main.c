#include "pico/stdlib.h"
#include <stdio.h>
#include "thread_handler.h"

void example_task(void *arg) {
    printf("Executing example task with arg: %d\n", *(int *)arg);
    sleep_ms(1000); 
}

int main() {
    stdio_init_all();
    thread_handler_start();

    int arg1 = 42;
    thread_task_t *task1 = thread_handler_create_task(example_task, &arg1, "ExampleTask", HIGH, false);
    thread_handler_add_task(task1);

    sleep_ms(5000); // Allow time for execution
    
    thread_handler_remove_task(task1);
    thread_handler_stop();
    while(1)
    {
        printf("Heeey\n");
        sleep_ms(1000); 
    }
    return 0;
}