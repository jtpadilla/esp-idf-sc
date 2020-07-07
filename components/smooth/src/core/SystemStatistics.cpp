#include "smooth/core/logging/log.h"
#include "smooth/core/SystemStatistics.h"
#include <fmt/core.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#pragma GCC diagnostic pop

using namespace smooth::core::logging;

static constexpr const char* tag = "MemStat";

namespace smooth::core
{
    TaskStats::TaskStats(uint32_t stack_size)
            : stack_size(stack_size)
    {
        high_water_mark = ::uxTaskGetStackHighWaterMark(nullptr);
    }

    static constexpr const char* dump_fmt = "{:>8} | {:>11} | {:>14} | {:>12} | {:>11} | {:>14} | {:>12}";

    void SystemStatistics::dump() const noexcept
    {
        Log::info(tag, "");
        Log::info(tag, dump_fmt,
            "Mem type",
            "8-bit free",
            "Smallest block",
            "Minimum free",
            "32-bit free",
            "Smallest block",
            "Minimum free"
        );
        Log::info(tag, dump_fmt,
            "--------",
            "----------",
            "--------------",
            "------------",
            "-----------",
            "--------------",
            "------------"
        );

        dump_mem_stats("INTERNAL", MALLOC_CAP_INTERNAL);
        dump_mem_stats("DMA", MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
        dump_mem_stats("SPIRAM", MALLOC_CAP_SPIRAM);

        { 
            // Only need to lock while accessing the shared data
            std::lock_guard<std::mutex> guard{ lock };
            constexpr const char* stack_format = "{:>16} | {:>10} | {:>15} | {:>15}";
            Log::info(tag, "");
            Log::info(tag, stack_format, "Name", "Stack", "Min free stack", "Max used stack" );
            Log::info(tag, stack_format, 
                "----------------", 
                "----------", 
                "---------------", 
                "---------------"
            );

            for (const auto& stat : task_info)
            {
                Log::info(
                    tag,
                    stack_format,
                    stat.first,
                    stat.second.get_stack_size(),
                    stat.second.get_high_water_mark(),
                    stat.second.get_stack_size() - stat.second.get_high_water_mark()
                );
            }
            Log::info(tag, "");
        }
    }

    void SystemStatistics::dump_mem_stats(const char* header, uint32_t caps) const noexcept
    {
        Log::info(tag, dump_fmt, 
            header,
            ::heap_caps_get_free_size(caps | MALLOC_CAP_8BIT),
            ::heap_caps_get_largest_free_block(caps | MALLOC_CAP_8BIT),
            ::heap_caps_get_minimum_free_size(caps | MALLOC_CAP_8BIT),
            ::heap_caps_get_free_size(caps | MALLOC_CAP_32BIT),
            ::heap_caps_get_largest_free_block(caps | MALLOC_CAP_32BIT),
            ::heap_caps_get_minimum_free_size(caps | MALLOC_CAP_32BIT)
        );
    }

}
