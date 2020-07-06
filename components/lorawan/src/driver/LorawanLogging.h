#pragma once

#if LMIC_ENABLE_event_logging

#include <freertos/FreeRTOS.h>
#include <freertos/ringbuf.h>

namespace genielink::lorawan::driver
{
        
    /**
     * @brief Logging class.
     * 
     * Logs internal information from LMIC in an asynchrnous fashion in order
     * not to distrub the sensitive LORA timing.
     * 
     * A ring buffer and a separate logging task is ued. The LMIC core records
     * relevant values from the current LORA settings and writes them to a ring
     * buffer. The logging tasks receives the message and the values, formats
     * them and outputs them via the regular ESP-IDF logging mechanism.
     * 
     * In order to activate the detailed logging, set the macro
     * `LMIC_ENABLE_event_logging` to 1.
     * 
     * This class is not to be used directly.
     */
    class LorawanLogging {

        public:
            static LorawanLogging* initInstance();

            void init();
            void logEvent(int event, const char* message, uint32_t datum);

        private:
            static void loggingTask(void* param);
            static void logFatal(const char* file, uint16_t line);

            RingbufHandle_t ringBuffer;

    };

}

#endif

