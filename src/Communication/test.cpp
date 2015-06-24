#include <iostream>
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
        c.stop_stream();

        c.get_data(tmp);

        for (int i = 0; i < 512; i++) {
            cout << tmp[i];

            if (i % 10 == 0)
                cout << endl;
        }
    }
    else {
        cout << "\nCould not connect to " << host << endl;
    }

    return 0;
}
