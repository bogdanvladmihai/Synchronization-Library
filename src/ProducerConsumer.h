#include "semaphore.h"
#include <deque>

/**
 * int no_items;
 * T item;
 * ProducerConsumer PC(no_items);
 * PC.add_item(item);
 * item = PC.get_item(); 
 * 
*/

template <class T>
class ProducerConsumer {
private:
  std::deque<T> items;
  Mutex mutex;
  Semaphore available_items;
  Semaphore free_spaces;


public:
  ProducerConsumer(int buff_size);
  void add_item(const T& item);
  T get_item();
};

#include "ProducerConsumer.cpp"