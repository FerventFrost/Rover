#ifndef BYTE_QUEUE_H
#define BYTE_QUEUE_H

#include <Arduino.h>

class ByteQueue {
private:
    char * queueArray;
    size_t maxSize;
    size_t frontIndex;
    size_t rearIndex;
    size_t currentSize;

public:
    ByteQueue(size_t size);
    ~ByteQueue();

    bool enqueue(const char* data, size_t length);
    bool dequeue(char* data, size_t length);
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
};

#endif
