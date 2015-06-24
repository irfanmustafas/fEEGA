#include <string>
#include <fftw3.h>
#include <fstream>

void load_data(
        int inverse,
        void *data,
        std::string path,
        int ncount)
{
    double* dp;
    fftw_complex *cp;
    int k;
    ifstream iFile;
    double real, imag, mag;
    char buffer[256];

    if (inverse)
        cp = (fftw_complex*)data;
    else
        dp = (double*)data;

    if (iFile.open(path))
    {
        while (iFile.getline(buffer, 256))
        {
            cp[k][0] = (double)strtok(buffer, " ");
        }
        /*
        for (eof = k = 0; k < ncount; k++)
        {
            if (inverse)
                if (eof || 
        }
        */
    }

}
