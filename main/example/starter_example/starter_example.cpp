
#include "starter_example.h"
#include "smooth/core/Task.h"
#include "smooth/core/task_priorities.h"
#include "smooth/core/SystemStatistics.h"

using namespace smooth::core;

namespace starter_example
{
    class ATask : public smooth::core::Task
    {
        public:
            ATask() : smooth::core::Task("Other task", 9000, APPLICATION_BASE_PRIO, std::chrono::seconds{ 1 })
            {}

            void tick() override
            {
                Log::info("App::Init", "Hello from other task");
            }
    };

    ATask a_instance{};

    App::App()
            : Application(smooth::core::APPLICATION_BASE_PRIO, std::chrono::seconds(3))
    {
    }

    void App::init()
    {
        Log::info("App::Init", "Starting...");
        a_instance.start();
    }

    void App::tick()
    {
        Log::info("App", "Hello world!");
        SystemStatistics::instance().dump();
    }
}
