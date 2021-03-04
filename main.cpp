#include "mbed.h"

#define TX PA_9
#define RX PA_10
#define BAUDRATE 9600

using namespace std::chrono_literals;
using namespace std::chrono;

static BufferedSerial uart(TX, RX, BAUDRATE);
static DigitalOut led(PB_5);
static DigitalOut led2(PB_4);
static DigitalIn btn3(PA_3, PullUp);
static DigitalIn btn2(PA_2, PullUp);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &uart;
}

// main() runs in its own thread in the OS
int main()
{
    Timer t, t2;
    //uart.set_blocking(false);
    t.start();
    t2.start();
    int elapsed = 0, elapsed2 = 0;
    int percent = 500;
    while (true) 
    {
        elapsed = duration_cast<milliseconds>(t.elapsed_time()).count();
        elapsed2 = duration_cast<milliseconds>(t2.elapsed_time()).count();
        if (elapsed > (120 * percent) / 1000)
        {
            led = !led;
            t.reset();
        }
        if (elapsed2 > (240 * percent) / 1000)
        {
            led2 = !led2;
            t2.reset();
        }
        if (!btn2)
        {
            if (percent < 1000)
                percent ++;
        }
        if (!btn3)
        {
            if (percent > 0)
                percent --;
        }
        printf("%d\n", percent);
    }
}

 /*if (uart.readable())
        {
            char s = ' ';
            uart.read(&s, 1);
            uart.write(&s, 1);
        }*/
        //printf("Please input value");
        //scanf("%f", c);
        //printf("Value is: %f\n", &c);
        //ThisThread::sleep_for(1s);


        //ThisThread::sleep_for(1s);
        //printf("Elapsed %llu mcs %d\n", 
        //duration_cast<microseconds>(t.elapsed_time()).count(), 
        //SystemCoreClock);