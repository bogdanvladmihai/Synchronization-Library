#include "semaphore.h"

template <class T>
class ProducerConsumer {
private:
  std::vector<T> items;
  Mutex mutex;
  Semaphore available_items;
  Semaphore free_spaces;

public:
  ProducerConsumer(int buff_size);
  void add_item(const T& item);
  T& get_item();
};

#include "ProducerConsumer.cpp"