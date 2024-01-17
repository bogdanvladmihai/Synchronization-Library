# Synchronization-Library

This is a C++ synchronization library implemented only using atmoic primitives such as `std::atomic_flag_test_and_set_explicit` and `std::atomic_flag_clear_explicit`.

The library provides implementations for various synchronization tools. 

* **Mutexes**

Simple mutex object to provide mutual exclusion.
```c++
Mutex lock;
lock.lock();
lock.unlock();
 
if (lock.try_lock()) {
  critical zone
  lock.unlock();
} else {
  non critical zone
}
```

* **Timed Mutex**

Mutex object that also provides the possibility of trying to obtain a lock for a fixed period of time.
```c++

TimedMutex lock;
if (lock.try_lock_for(50)) {
  cricical zone;
  lock.unlock();
} else {
  non critical zone;
}
```

* **LockGuard and ScopedLock**


The lock guard is a wrapper for a mutex that automatically acquires the lock on construction and releases it on destruction, ensuring proper mutex management within a specific scope. Scoped locks generalize this conecpt for an arbitrary number of locks. Note that both objects can be used with timed mutexes as well.
```c++
Mutex counter_lock;
int count = 0;

bool add_one() {
  LockGuard lock(counter_lock);
  critical zone
  if (count == LIMIT) {
   return false;
  }
  count += 1;
  return true;
}
```

```c++
Mutex m1, m2, m3;

void func() {
  vector<Mutex&> guards = {m1, m2, m3};
  ScopedLock lock(guards);
  cricital zone
}

```

* **Semaphore**

Simple busy-waiting semaphore object. 
```c++
Semaphore S(3);

S.signal();
S.wait();
```

* **Barrier**

Object used to crate a barrier for a fixed number of threads.
```c++
const int WORKERS = 100;

std::vector<std::thread> threads;
Barrier barrier(WORKERS);

for (int i = 0; i < N; i++) {
  threads.push_back(std::thread([&barrier]() {
    work before the barrier point

    barrier.barrier_point();
    
    work after all the threads passed the barrier
  }));
}
```

* **ReusableBarrier**

Reusable barrier barrier object.
```c++
const int WORKERS = 100;

std::vector<std::thread> threads;
ReusableBarrier barrier(WORKERS);

for (int i = 0; i < N; i++) {
  threads.push_back(std::thread([&barrier]() {
    work before the barrier point

    barrier.barrier_point();
    
    work after all the threads passed the barrier

    barrier.barrier_point();

    work after all the threads passed the second barrier
  }));
}
```

* **Lightswitch**

Simple lightswitch object.

```c++
Semaphore s;
Lightswitch L;

L.close(s);
L.open(s);
```

* **ProducerConsumer**

Object that provides support for the producer-consumer problem. The objects are retunred in order of production.
```c++
const int BUFFER_SIZE = 500;

ProducerConsumer<int> PC(BUFFER_SIZE);

std::vector<std::thread> threads;
for (int i = 0; i < PRODUCERS_COUNT; i++) {
  threads.push_back(std::thread([&PC]() {
    auto item = get_item();
    PC.add_idem(item);
  }));
}
for (int i = 0; i < CONSUMERS_COUNT; i++) {
  threads.push_back(std::thread([&PC]() {
    auto item = PC.get_item();
  }));
}
```

* **RW_NoStarve and RW_WriterPriority**

Objects to solve the readers-writers problem. Depending on the situation, you can choose a NoStarve object or an object that prioritizes writers.
```c++
const int WORKERS = 500;

RW_NoStarve rwlock;

std::vector<std::thread> threads;
for (int i = 0; i < WORKERS; i++) {
  if (i % 2 == 1) {
    threads.push_back(std::thread ([&rwlock]() {
      RW.aquire_reader();
      reader code
      RW.release_reader();
    }));
  } else {
    threads.push_back(std::thread ([&rwlock]() {
      RW.aquire_writer();
      writer code
      RW.release_writer();
    }));
  }
}
```


The library was implemented by *Vlad-Mihai Bogdan* and *Cristiana Cocheci*.
