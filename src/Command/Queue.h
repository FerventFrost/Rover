#ifndef BYTE_QUEUE_H
#define BYTE_QUEUE_H

#include <Arduino.h>
#include "StructPlan.h"

class Node {
public:
    byte* data;
    size_t length;
    Node* next;

    Node(byte* data, size_t length);
    ~Node();
};

class ByteQueue {
private:
    Node* front;
    Node* rear;
public:
    ByteQueue();
    ~ByteQueue();

    bool enqueue(byte* data, size_t length);
    bool dequeue(byte* data, size_t length);
    bool isEmpty() const;
};

#endif
