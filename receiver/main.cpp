
#include "ReciverRtl.hpp"

int main(int argc, char **argv) {
    init_struct_receiver init_start =
    {
        60 * 1000000,
        2048000,
        0,
        10
    };

    ReciverRtl num1(init_start, 0);
    ReciverRtl num2(init_start, 1);


}
