#include <mbed.h>
#include <rtos.h>
#include <mbed_events.h>

DigitalOut red(LED1,1);
void flash(void){
    red = !red;
}
DigitalOut green(LED2,1);
void blink(void){
    green = !green;
}

Serial pc(USBTX, USBRX);
Thread worker;
EventQueue queue ;

Thread thread;

int main() {
    pc.printf("ready");
    queue.call_every(500, flash);
    queue.call_every(300, blink);

    pc.printf("dispatching...");
    //EventQueue will not execute until this method is called.
    queue.dispatch_forever();

    worker.start(callback(&queue, &EventQueue::dispatch_forever ));
    pc.printf("dispatched");
    while(1){}
}
