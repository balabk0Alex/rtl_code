#include <libusb-1.0/libusb.h>
#include <iostream>
#include <vector>

#define SIZE_KNOW_DEVICE 2

struct RTLSDR_KNOW_DEVICE
{
    uint16_t idVendor;
    uint16_t idProduct;

    const char * NameModel;
};

struct RTL_LIST
{
    const char * NameModel;
    libusb_device * dev;


};

class Rtl_connect_process
{
public:
    Rtl_connect_process();
    ~Rtl_connect_process();
    //here programm start
    void run();
private:
    bool menu();
    void update();
    void check_idip(libusb_device * dev, std::vector<RTL_LIST> & out);
    void show();

    libusb_context *ctx;

    RTLSDR_KNOW_DEVICE DEV_KNOW_LIST[SIZE_KNOW_DEVICE] = {
        { 0xbda, 0x2832, "Generic RTL2832U"},
        { 0xbda, 0x2838, "Generic RTL2832U OFM"}

    };

    std::vector<RTL_LIST> actual_list;

};
