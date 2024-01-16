#include "ReadersWriters.h"

RW_NoStarve::RW_NoStarve():roomIsEmpty(1){}

  void RW_NoStarve::aquire_reader() {
    no_starve_writer_gate.lock();
    no_starve_writer_gate.unlock();
    readSwitch.close(roomIsEmpty);
     ///now reading
  }
  void RW_NoStarve::release_reader() {
    readSwitch.open(roomIsEmpty);
  }
  void RW_NoStarve::aquire_writer() {
    no_starve_writer_gate.lock();
      roomIsEmpty.wait();
      ///now writing
  }
  void RW_NoStarve::release_writer() {
    no_starve_writer_gate.unlock();
    roomIsEmpty.signal();
  }


RW_WriterPriority::RW_WriterPriority(): noReaders(1), noWriters(1){}
  void RW_WriterPriority::aquire_writer() {
    writeSwitch.close(noReaders);
      noWriters.wait();
      ///now writing
  }
  void RW_WriterPriority::release_writer(){
    noWriters.signal();
    writeSwitch.open(noReaders);
  }

  void RW_WriterPriority::aquire_reader(){
    noReaders.wait();
    readSwitch.close(noWriters);
    noReaders.signal();
     ///now reading
  }
  void RW_WriterPriority::release_reader() {
    readSwitch.open(noWriters);
  }
