#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_event.h>
#pragma GCC diagnostic pop

#include "smooth/core/Application.h"
#include "smooth/core/network/SocketDispatcher.h"
#include "smooth/core/filesystem/FSLock.h"

using namespace smooth::core::filesystem;
using namespace smooth::core::logging;
using namespace std::chrono;

namespace smooth::core
{
    EarlyInit::EarlyInit(uint32_t priority, const std::chrono::milliseconds& tick_interval)
        : Task(priority, tick_interval)
    {
        // Place things here that needs to initialize early in the application startup.
        nvs_flash_init();
        gpio_install_isr_service(0);
        esp_event_loop_create_default();

        // Set the number of allowed open files to something reasonable that might be
        // used when running on the ESP. can be changed later.
        FSLock::set_limit(5);
    }

    EarlyInit::~EarlyInit()
    {
        esp_event_loop_delete_default();
        gpio_uninstall_isr_service();
        nvs_flash_deinit();
    }

    void Application::init()
    {
        // Start socket dispatcher first of all so that it is
        // ready to receive network status events.
        network::SocketDispatcher::instance();

        if (get_wifi().is_configured())
        {
            get_wifi().connect_to_ap();
        }
    }
    
}
