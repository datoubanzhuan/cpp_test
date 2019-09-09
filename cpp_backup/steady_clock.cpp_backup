#include <chrono>
#include <iostream>
#include <thread>
#include "utility.hpp"

int main()
{
    for (int32_t i = 0;; i++)
    {
        uint64_t time1 = Utility::getTimeStamp();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
        uint64_t time2 = Utility::getTimeStamp();
        int32_t interval = time2-time1;
        std::cout << "time1: " << time1 << ", time2: " << time2 << ", interval: " << interval << std::endl;
    }
    return 0;
}
