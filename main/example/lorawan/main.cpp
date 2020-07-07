#include "example/lorawan/SCExampleLauncher.h"
//#include "example/simpletask/TestTask.h"
//#include "example/fmt/ExampleFmt.h"
//#include "example/njson/ExampleNJson.h"

extern "C" void app_main(void)
{
    example::lorawan::launch();
    //example::simpletask::launch();
    //example::fmt::launch();
    //example::njson::launch();
}
