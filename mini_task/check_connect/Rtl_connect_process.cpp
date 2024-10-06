#include "Rtl_connect_process.hpp"




Rtl_connect_process::Rtl_connect_process()
{
    int r = libusb_init(&ctx);
    if(r < 0 )
    {
        std::cout << "ERROR: initialization don't execute " << std::endl;
        exit(1);
    }

     libusb_set_debug(ctx, 3);
}

Rtl_connect_process::~Rtl_connect_process()
{
    libusb_exit(ctx);
}

void Rtl_connect_process::run()
{
    std::cout << "Welcome!\
    This program able to show RTL list which connect with PC\n";

    while( menu() )
    {

    }
}

void Rtl_connect_process::update()
{
    libusb_device ** devs;
    size_t cnt = libusb_get_device_list(ctx, &devs);

     if(cnt < 0){
        std::cout << "ERROR: list of usb devise don't get" << std::endl;
    }

    actual_list.clear();
    for(int i = 0; i < cnt;++i)
        check_idip(devs[i], actual_list);


    libusb_free_device_list(devs,1);
}


bool Rtl_connect_process::menu()
{
    int menu_choose;

    std::cout << "MENU:\n"
    "1.UPDATE LIST\n"
    "0.EXIT\n";

    std::cin >> menu_choose;

    if(menu_choose)
    {
        update();
        show();
        return true;
    }
    else
        return false;
}

void Rtl_connect_process::check_idip(libusb_device* dev, std::vector<RTL_LIST>& out)
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);

    if( r < 0)
        std::cout << "ERROR: descriptor of device don't get" << std::endl;

    for(int i = 0;i < SIZE_KNOW_DEVICE; ++ i)
    {
        if(DEV_KNOW_LIST[i].idProduct == desc.idProduct && DEV_KNOW_LIST[i].idVendor == desc.idVendor )
        {
            out.push_back({DEV_KNOW_LIST[i].NameModel, dev});
            return ;
        }
    }
}

void Rtl_connect_process::show()
{
    if(!actual_list.size())
        std::cout << "Devise don't found" << std::endl;
    for(int i = 0; i < actual_list.size(); ++ i)
    {
        std::cout << i + 1<< "." << actual_list[i].NameModel << std::endl;
    }
}


