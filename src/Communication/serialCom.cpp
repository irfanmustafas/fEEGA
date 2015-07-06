//#include <termios.h>
#include <boost/asio.hpp>
#include <string>

class Serial
{
public:
    Serial(std::string port,
           unsigned int baud_rate=115200):
        io(), serial(io, port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    std::string readLine()
    {
        using namespace boost;
        char c;
        std::string result;

        while(true)
        {
            asio::read(serial, asio::buffer(&c, 1));
            switch(c)
            {
                case '\r':
                    break;
                case '\n':
                    return result;
                default:
                    result+=c;
            }
        }
    }

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};
//SimpleSerial serial("/dev/tty.usbxx",115200); // get SimpleSerial class on link above
