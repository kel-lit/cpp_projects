#include <iostream>
#include <Windows.h>
#include "mingw.thread.h" //For some reason <thread> isn't working with my gcc.

static int current = 0;
static bool locked = false;
static bool work_finished = false;

void work(){

    while (!work_finished){
        
        if (!locked) {
            locked = true;
            std::cout << current << std::endl;
            current++;
            locked = false;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main(){

    
    std::thread worker1(work);
    std::thread worker2(work);
    std::thread worker3(work);

    while (current < 20);

    work_finished = true;

    worker1.join();
    worker2.join();
    worker3.join();

    return 0;

}