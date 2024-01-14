#include "ProducerConsumer.h"

ProducerConsumer::ProducerConsumer(int buff_size): available_items(0), free_spaces(buff_size){}

void ProducerConsumer::add_item(T& item){
  free_spaces.wait();
  mutex.lock();
    items.push_back(item);
  mutex.unlock();
  available_items.signal();    
}

T ProducerConsumer::get_item(){
  available_items.wait();
  mutex.lock();
    T item = items[items.size()-1];
    items.pop_back();
  mutex.unlock();
  free_spaces.signal();
  return item;
}

int main(){
  return 0;
}