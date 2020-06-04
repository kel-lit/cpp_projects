#include <iostream>
#include "mingw.thread.h" //For some reason <thread> isn't working with my gcc.

using namespace std;

static bool worker_finished = false;

void DoWork(){


    while (!worker_finished){

        cout << "Working... \n";
        this_thread::sleep_for(chrono::seconds(1));

    }

    return;
}

int main(){

    cout << "Press enter to stop worker thread\n";

    thread worker(DoWork);

    cin.get();
    worker_finished = true;

    worker.join();
    cout << "Finished\n";

    return 0;
}