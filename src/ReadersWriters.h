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

class RW_NoStarve : public ReadersWriters{
private:
  Semaphore roomIsEmpty;
  Mutex no_starve_writer_gate;
public:
  RW_NoStarve();
  void aquire_reader() override;
  void release_reader() override;
  void aquire_writer() override;
  void release_writer() override;
};

class RW_WriterPriority: public ReadersWriters{
private:
  Lightswitch writeSwitch;
  Semaphore noReaders;
  Semaphore noWriters;
public:
  WriterPriority();
  void aquire_writer() override;
  void release_writer() override;

  void aquire_reader() override;
  void release_reader() override;
};