#include "../Communication/tcp_client.h"

#define SIZE 512

template <typename Comm>
class Fft
{
public:
    Fft(Comm& c,
        int window_size,
        std::string ip,
        int port):
        comm(c),
        _window_size(window_size),
        _ip(ip),
        _port(port)
    {
        comm.conn(_ip, _port);
        comm.start_stream();
    }

    ~Fft()
    {
        comm.stop_stream();
    }

    void get_freqs(double freqs[][])
    {
        freqs = fft_window;
    }

private:
    void load_fft()
    {
        double in[SIZE];
        /*
        fftw_r2r_kind kind[8];

        for (int i = 0; i < rank; i++)
            kind = FFTW_R2HC;
        */

        //in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
        //out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);

        fftw_plan plan = fftw_plan_r2r_1d(SIZE,
                                       in,
                                       fft_window[0],
                                       FFTW_REDFT11,
                                       FFTW_MEASURE);

        fftw_execute(plan);

        fftw_destroy_plan(plan);
        fftw_free(in);
    }

    double fft_window[8][_window_size];
    int _window_size;
    int _port;
    std::string _ip;
    Comm comm;
};
