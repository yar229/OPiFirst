#pragma once

#include <chrono>

void PrintDatetime(std::time_t time);
void timer_start(std::function<void(time_t)> func, unsigned int interval);