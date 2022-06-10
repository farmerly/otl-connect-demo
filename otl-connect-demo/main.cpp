#include "otl_control.h"

int main()
{
    const char connStr[] = "zxht/zxht1234@127.0.0.1:1521/orcl";
    otl::OtlController controller;
    controller.initialize(connStr);
    if (controller.connect()) {
        controller.connectionTest();
        controller.disconnect();
    }
    return 0;
}