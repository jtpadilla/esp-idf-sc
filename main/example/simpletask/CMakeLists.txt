idf_component_register(
    SRCS 
        "main.cpp" 

        "example/lorawan/CounterStatistics.cpp" 
        "example/lorawan/CounterStatistics.h" 
        "example/lorawan/SCExampleLorawanTask.cpp" 
        "example/lorawan/SCExampleLorawanTask.h" 
        "example/lorawan/SCExampleLauncher.cpp" 
        "example/lorawan/SCExampleLauncher.h" 

        "example/simpletask/TestTask.cpp" 
        "example/simpletask/TestTask.h" 

        "example/fmt/ExampleFmt.cpp" 
        "example/fmt/ExampleFmt.h" 

        "example/njson/ExampleNJson.cpp" 
        "example/njson/ExampleNJson.h" 

        REQUIRES os sys lorawan fmt nlohmann_json
        
)