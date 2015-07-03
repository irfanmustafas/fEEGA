//#include <array>
#include <atomic>
#include <iostream>

template <typename Type>
class RingBuffer
{
public:
    RingBuffer(int buffer_size=512,
               int num_chan=8):
        _buffer_size(buffer_size),
        _num_channels(num_chan)
    {
        // Clear channel data buffer
        for (int i = 0; i < num_chan; i++)
            for (int j = 0; j < buffer_size; j++)
                channel_data[i][j] = 0;

        // Initialize current position pointer
        cur_pos = 0;
    }

    void write(const float sample[])
    {
        std::cout << "Cur pos: " << cur_pos << std::endl;

        // Need to assert that sample size is correct
        for (int i = 0; i < _num_channels; i++)
            channel_data[cur_pos][i] = sample[i];

        // Update current position
        cur_pos = (cur_pos + 1) % _buffer_size;
    }

    void read(Type wind_buffer[], int chan)
    {
        int cur = 0;
        int tail = cur_pos;

        for (; cur < _buffer_size; cur++)
            wind_buffer[cur] = channel_data[chan][cur];

        for (int i = 0; i < tail; i++, cur++)
            wind_buffer[cur] = channel_data[chan][0];
    }

private:
    const int _num_channels;
    const int _buffer_size;
    float channel_data[512][8];
    //std::array<Type, _num_channels> channel_data;
    Type T;
    std::atomic<int> cur_pos;
};
