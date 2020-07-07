# DemoZMQ
Demonsrate zmq patterns flow


# ZeroMQ push/pull pattern
Similar to the pub/sub pattern, in the push/pull pattern you have one side (the PUSH socket) that's doing all the sending, where the other side (PULL) does all the receiving. 
The difference between push/pull and pub/sub is that in push/pull, each message is routed to a single PULL socket, whereas in pub/sub, each message is broadcast to all the SUB sockets. 
The push/pull pattern is useful for pipelined workloads where a worker process performs some operations and then sends results along for further processing. 
It's also useful for implementing traditional message queues.

![alt text](https://github.com/booksbyus/zguide/raw/master/images/fig5.png)
