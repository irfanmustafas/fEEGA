#include <fftw3.h>

#define SIZE 512

void Fft::load_fft()
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
