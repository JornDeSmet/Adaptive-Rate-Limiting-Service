#include "RateLimiter.h"
#include <iostream>
#include <thread>

int main() {
    RateLimiter limiter(4, std::chrono::seconds(1));

    for (int i = 0; i < 5; i++) {
        std::cout << limiter.allow("user") << "\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout <<limiter.allow("user") << "\n";
}