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
    //close(server);
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
    run_stream = true;
    stream_thread = std::thread(&TCPclient::tcp_stream, this);
}

void TCPclient::stop_stream()
{
    run_stream = false;
    stream_thread.join();
}

void TCPclient::tcp_stream()
{
    float tmp_vals[RANK];

    while (run_stream)
    {
        // Store recieved packet in channel_data
        for (int chan = 0; chan < RANK; chan++) {
            try {
                receive(tmp_vals, RANK);
            }
            catch (const std::invalid_argument& ia) {
                std::cerr << "Invalid argument: " << ia.what();
            }
            //std::cout << tmp_vals[chan] << "  ";
        }
        //std::cout << std::endl;

        channel_data.write(tmp_vals);
    }
    std::cout << "Stream finished\n";
}

bool TCPclient::receive(float vals[], int vals_size)
{
    unsigned char buffer[vals_size*4];
    int byte_count;

    int count = 0;
    char* ptr = nullptr;

    // Receive a reply from the server
    byte_count = recv(sock, buffer, vals_size, 0);

    if (byte_count < 0)
    {
        std::cout << "Receive failed..." << std::endl;
    }

    // Convert to little endian and transfer populate float vector
    for (int i = 0; count < vals_size; i += 4, count++) {

        ptr = (char*)(vals + count);

        ptr[3] = buffer[i];
        ptr[2] = buffer[i+1];
        ptr[1] = buffer[i+2];
        ptr[0] = buffer[i+3];

        std::cout << "Val[" << count << "] " << vals[count] << std::endl;
    }

    return true;
}

void TCPclient::get_data(float tmp[])
{
    channel_data.read(tmp, 0);
}
