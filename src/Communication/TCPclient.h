#include <string>
//#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netdb.h>
#include <thread>
#include <atomic>

#include "ring_buffer.hpp"

// Debugging purposes
#include <iostream>

#define RANK 8

class TCPclient
{
    public:
        TCPclient() {}
        bool conn(std::string, int);
        bool close();
        bool send_data(std::string data);
        void start_stream();
        void stop_stream();
        void get_data(float tmp[]);

    private:
        void tcp_stream();
        float interpFloat(char*);
        bool receive(float vals[], int vals_size);

        RingBuffer<float> channel_data;
        int sock;
        int port;
        std::string address;
        struct sockaddr_in server;
        std::thread stream_thread;
        std::atomic<bool> run_stream;
};
