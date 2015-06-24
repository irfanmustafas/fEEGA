//#include <array>
#include <atomic>

template <typename Type>
class RingBuffer
{
public:
    RingBuffer(int buffer_size=512,
               int num_chan=8):
        _buffer_size(buffer_size),
        _num_channels(num_chan)
    {}

    void write(const float sample[])
    {
        // Need to assert that sample size is correct
        for (int i = 0; i < _num_channels; i++)
            channel_data[cur_pos][i] = sample[i];
    }

    void read(Type wind_buffer[], int chan)
    {
        int cur = 0;
        int tail = cur_pos;

        for (int i = cur_pos; i < _buffer_size; i++, cur++)
            wind_buffer[cur] = channel_data[chan][i];

        for (int i = 0; i < tail; i++, cur++)
            wind_buffer[cur] = channel_data[chan][i];
    }

private:
    const int _num_channels;
    const int _buffer_size;
    float channel_data[8][512];
    //std::array<Type, _num_channels> channel_data;
    Type T;
    std::atomic<int> cur_pos;
};
