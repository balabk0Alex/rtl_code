#pragma once
#include <iostream>
#include <rtl-sdr.h>


struct init_struct_receiver
{
    uint32_t frecuency;
    uint32_t samp_rate ;
    int gain;
    int ppm_error;
};
//dev index other
/*todo: set limits*/

class ReciverRtl
{
public:
    ReciverRtl( init_struct_receiver init, int dev_n)
    {
        int r;
        std::cout << "Activate device number:" << dev_n << std::endl;
        rtlsdr_open(&main_dev, dev_n);
        if (r < 0)
            std::cout << "Failed to open rtlsdt device" << std::endl;

        r = rtlsdr_set_sample_rate(main_dev,init.samp_rate);
        if(r < 0)
        {
            std::cout << "Failed to set sample rate" << std::endl;
            exit(1);
        }
        else
            std::cout << "Set sample_rate:" << init.samp_rate << std::endl;


        r = rtlsdr_set_center_freq(main_dev,init.frecuency);
        if(r < 0)
        {
            std::cout << "Failed to set frecuency" << std::endl;
            exit(1);
        }
        else
            std::cout << "Set frecuency:" << init.frecuency << "Hz" <<  std::endl;


        if(init.gain)
        {
           r = rtlsdr_set_tuner_gain_mode(main_dev, 1);

           if(r < 0)
           {
               std::cout << "Failed to set manuai gain" << std::endl;
               exit(1);}
            r = rtlsdr_set_tuner_gain(main_dev, init.gain);
            if(r < 0)
           {
               std::cout << "Failed to set gain" << std::endl;
               exit(1);}
            else
            {
                std::cout << "Set gain:" << init.gain << std::endl;
            }

        }
        else{
             r = rtlsdr_set_tuner_gain_mode(main_dev, 0);
             if(r < 0)
                 {
            std::cout << "Failed to set automatic gain mode" << std::endl;
            exit(1);
        }
        }

        r = rtlsdr_set_freq_correction(main_dev, init.ppm_error);

        if(r < 0)
        {
            std::cout << "Failed to set frecuency correction" << std::endl;
            exit(1);
        }
        else
            std::cout << "Set frecuency correction:" << init.ppm_error <<std::endl;

        std::cout << "SUCSESSS;" << std::endl;
    }



    rtlsdr_dev_t* main_dev{nullptr};
};

