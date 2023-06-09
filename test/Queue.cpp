#include <iostream>
#include "ByteQueue.h"

int main()
{
    ByteQueue queue(10);
    queue.enqueue("Hello", 5);
    queue.enqueue("World", 5);
    queue.enqueue("!", 1);
    queue.enqueue("Baher", 5);
    queue.enqueue("!", 1);

    return 0;
}