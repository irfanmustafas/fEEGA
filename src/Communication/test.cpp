#include <iostream>
#include <iomanip>
#include "TCPclient.h"

using namespace std;

int main() {
    TCPclient c;
    //string host = "74.125.236.200";
    string host = "127.0.0.1";
    float tmp[512] = {0};

    if (c.conn(host, 12345))
    {
        c.start_stream();
        cout << "Started stream\n";
        cin.ignore();
        cout << "Thanks for your input\n";
        c.stop_stream();

        cout << "Retrieving data...\n";
        c.get_data(tmp);

        cout << scientific << setprecision(7);
        for (int i = 0; i < 512; i++) {
            cout << setw(15) << tmp[i];

            if (i % 8 == 0)
                cout << endl;
        }
    }
    else {
        cout << "\nCould not connect to " << host << endl;
    }

    return 0;
}
