#include "TCPclient.h"

#include <string.h> // strlen
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <thread>

// Debugging purposes
#include <iostream>

using namespace std;

bool TCPclient::conn(std::string address, int port)
{
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        perror("Could not create socket");
    }

    //std::cout << "Created socket..." << std::endl;

    // Setup ip structure
    server.sin_addr.s_addr = inet_addr(address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Connecto to server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("Connection failed.");
        return false;
    }

    std::cout << "Connected to: " << address << std::endl;

    return true;
}

bool TCPclient::close()
{
    //server.close();
}

bool TCPclient::send_data(string data)
{
    if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0)
    {
        perror("Send failed...");
        return false;
    }

    std::cout << "Data sent..." << std::endl;

    return true;
}

void TCPclient::start_stream()
{
    stream_thread = std::thread(&TCPclient::tcp_stream, this);
}

void TCPclient::stop_stream()
{
    stream_thread.join();
}

void TCPclient::tcp_stream()
{
    float tmp[RANK];
    std::string packet;

    while (true)
    {
        for (int i = 0; i < 512; i++) {
            // Store recieved packet in channel_data
            for (int chan = 0; chan < 8; chan++) {
                try {
                    packet = receive();
                    //tmp[i] = std::stof(packet);
                }
                catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what()
                              << " (" << packet << ")\n";
                }
            }

            //std::lock_guard<std::mutex> guard(mx);
            channel_data.write(tmp);
        }
    }
}

std::string TCPclient::receive()
{
    int size = 32;
    char buffer[size];
    int byte_count;

    float vals[8];
    int count = 0;
    int t;

    // Receive a reply from the server
    byte_count = recv(sock, buffer, size, 0);
    //std::cout << "Byte count: " << byte_count << std::endl;

    if (byte_count < 0)
    {
        std::cout << "Receive failed..." << std::endl;
    }

    for (int i = 0; count < 8; i += 4, count++) {
        t =
                (buffer[i+3])       +
                (buffer[i+2] << 8)  +
                (buffer[i+1] << 16) +
                (buffer[i]   << 24);

        //vals[count] = *(float*)&t;
        vals[count] = *reinterpret_cast<float*>(&t);
        std::cout << "Val[" << count << "] " << vals[count] << std::endl;
    }
    std::cout << std::endl;

    return reply;
}

float TCPclient::interpFloat(char* buff)
{
    float x = (
            (0xFF & buff[0] << 24) |
            (0xFF & buff[1] << 16) |
            (0xFF & buff[2] << 8)  |
            (0xFF & buff[3]));

    return x;
}

void TCPclient::get_data(float tmp[])
{
    channel_data.read(tmp, 0);
}
