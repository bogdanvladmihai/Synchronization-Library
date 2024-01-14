#include "lightswitch.h"

class ReadersWriters{
protected:
  Lightswitch readSwitch;
public:
  ReadersWriters(){}
  virtual void aquire_reader() = 0;
  virtual void aquire_writer() = 0;
  virtual void release_reader() = 0;
  virtual void release_writer() = 0;
};

class NoStarve : public ReadersWriters{
private:
  Semaphore roomIsEmpty;
  Mutex no_starve_writer_gate;
public:
  NoStarve():roomIsEmpty(1){}
  void aquire_reader() override{
    no_starve_writer_gate.lock();
    no_starve_writer_gate.unlock();
    readSwitch.close(roomIsEmpty);
     ///now reading
  }
  void release_reader() override{
    readSwitch.open(roomIsEmpty);
  }
  void aquire_writer() override{
    no_starve_writer_gate.lock();
      roomIsEmpty.wait();
      ///now writing
  }
  void release_writer() override{
    no_starve_writer_gate.unlock();
    roomIsEmpty.signal();
  }
};

class WriterPriority: public ReadersWriters{
private:
  Lightswitch writeSwitch;
  Semaphore noReaders;
  Semaphore noWriters;
public:
  WriterPriority(): noReaders(1), noWriters(1){}
  void aquire_writer() override{
    writeSwitch.close(noReaders);
      noWriters.wait();
      ///now writing
  }
  void release_writer() override{
    noWriters.signal();
    writeSwitch.open(noReaders);
  }

  void aquire_reader() override{
    noReaders.wait();
    readSwitch.close(noWriters);
    noReaders.signal();
     ///now reading
  }
  void release_reader() override{
    readSwitch.open(noWriters);
  }
};