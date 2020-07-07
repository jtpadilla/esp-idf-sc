#include <unordered_map>
#include <mutex>

namespace smooth::core
{
    class TaskStats
    {
        public:
            TaskStats() = default;

            explicit TaskStats(uint32_t stack_size);

            TaskStats(const TaskStats&) = default;

            TaskStats(TaskStats&&) = default;

            TaskStats& operator=(const TaskStats&) = default;

            TaskStats& operator=(TaskStats&&) = default;

            [[nodiscard]] uint32_t get_stack_size() const noexcept
            {
                return stack_size;
            }

            [[nodiscard]] uint32_t get_high_water_mark() const noexcept
            {
                return high_water_mark;
            }

        private:
            uint32_t stack_size{};
            uint32_t high_water_mark{};
    };

    /// Muestra las estadisticas del sistema: uso de memoria y de stack.
    class SystemStatistics
    {
        public:
            using synch = std::lock_guard<std::mutex>;

            static SystemStatistics& instance()
            {
                static SystemStatistics instance{};

                return instance;
            }

            void report(const std::string& task_name, TaskStats&& stats) noexcept
            {
                synch guard{ lock };
                task_info[task_name] = stats;
            }

            void dump() const noexcept;

        private:
            void dump_mem_stats(const char* header, uint32_t caps) const noexcept;

            mutable std::mutex lock{};
            std::unordered_map<std::string, TaskStats> task_info{};

    };
}
