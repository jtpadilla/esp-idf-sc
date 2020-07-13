#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_event.h>
#pragma GCC diagnostic pop

#include "smooth/core/Application.h"

using namespace smooth::core::logging;
using namespace std::chrono;

namespace smooth::core
{
    EarlyInit::EarlyInit(uint32_t priority, const std::chrono::milliseconds& tick_interval)
        : Task(priority, tick_interval)
    {

        // Colocal aqui las inicializaciones que hay que realizar antes de iniciar la aplicacion
        nvs_flash_init();
        gpio_install_isr_service(0);
        esp_event_loop_create_default();

    }

    EarlyInit::~EarlyInit()
    {

        // Se detienen en oden inverso a como se realizo la inicializacion
        esp_event_loop_delete_default();
        gpio_uninstall_isr_service();
        nvs_flash_deinit();
        
    }

    void Application::init()
    {

    }
    
}
