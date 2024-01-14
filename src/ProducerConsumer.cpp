template<class T>
ProducerConsumer<T>::ProducerConsumer(int buff_size) : available_items(0), free_spaces(buff_size){}

template<class T>
void ProducerConsumer<T>::add_item(const T& item){
  free_spaces.wait();
  mutex.lock();
    items.push_back(item);
  mutex.unlock();
  available_items.signal();    
}

template<class T>
T ProducerConsumer<T>::get_item(){
  available_items.wait();
  mutex.lock();
    T item = items.front();
    items.pop_front();
  mutex.unlock();
  free_spaces.signal();
  return item;
}