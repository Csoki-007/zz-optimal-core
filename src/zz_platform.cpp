#include "zz_platform.h"

#if defined(ARDUINO)
#include <Arduino.h>
#if defined(ESP32)
#include <esp_system.h>
#endif
#elif defined(ESP_PLATFORM)
#include <esp_heap_caps.h>
#include <esp_system.h>
#include <esp_timer.h>
#include <esp_clk_tree.h>
#else
#include <chrono>
#endif

uint64_t zz_platform_now_us() {
#if defined(ARDUINO)
    return static_cast<uint64_t>(micros());
#elif defined(ESP_PLATFORM)
    return static_cast<uint64_t>(esp_timer_get_time());
#else
    using Clock = std::chrono::steady_clock;
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(
            Clock::now().time_since_epoch()).count());
#endif
}

size_t zz_platform_free_heap_bytes() {
#if defined(ARDUINO) && defined(ESP32)
    return static_cast<size_t>(ESP.getFreeHeap());
#elif defined(ESP_PLATFORM)
    return static_cast<size_t>(esp_get_free_heap_size());
#else
    return 0;
#endif
}

size_t zz_platform_min_free_heap_bytes() {
#if defined(ARDUINO) && defined(ESP32)
    return static_cast<size_t>(ESP.getMinFreeHeap());
#elif defined(ESP_PLATFORM)
    return static_cast<size_t>(heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
#else
    return 0;
#endif
}

uint32_t zz_platform_cpu_freq_mhz() {
#if defined(ARDUINO) && defined(ESP32)
    return static_cast<uint32_t>(getCpuFrequencyMhz());
#elif defined(ESP_PLATFORM)
    return static_cast<uint32_t>(esp_clk_cpu_freq() / 1000000U);
#else
    return 0;
#endif
}

void zz_platform_checkpoint() {
#if defined(ARDUINO)
    delay(1);
#elif defined(ESP_PLATFORM)
    // Give the scheduler a chance to run and keep watchdogs satisfied.
    vTaskDelay(1);
#else
    // No-op on desktop.
#endif
}
