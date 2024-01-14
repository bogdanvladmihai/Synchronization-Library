#include "semaphore.h"

class Lightswitch {
private:
    int counter;
    Mutex mutex;
public:
    Lightswitch() : counter(0){}
    void close(Semaphore & s){
        mutex.lock();
        counter++;
        if(counter ==1){
            s.wait();
        }
        mutex.unlock();
    }
    void open(Semaphore& s){
        mutex.lock();
        counter--;
        if(!counter){
            s.signal();
        }
        mutex.unlock();
    }
};