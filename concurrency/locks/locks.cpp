#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

static int counter = 0;
std::mutex mtx;

void work(){

    while (counter <= 20){
        mtx.lock();
        std::cout << "thread: " << std::this_thread::get_id()  << " counts: " << counter << std::endl;
        counter++;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}



int main(){

    std::thread worker1(work);
    std::thread worker2(work);
    std::thread worker3(work);

    while (counter <= 20){

        std::cout << "Main thread is doing some processing in the background" << std::endl;

        sleep(2);

        std::cout << "More main thread processing...." << std::endl;
        
        sleep(1);

    }

    std::cout << "All processing finished" << std::endl;

    worker1.join();
    worker2.join();
    worker3.join();

    return 0;
}