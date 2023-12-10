#ifndef RECORD_H
#define RECORD_H
#include "./map.h"

class Record
{
public:
    Record();
    ~Record();
    // 读入回放对象
    static Record* readrecord(QString path);
    static void writeRecord(QString path,Record *);
private:

};

#endif // RECORD_H
