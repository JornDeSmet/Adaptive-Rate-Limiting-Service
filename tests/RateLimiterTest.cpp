#include "../src/RateLimiter.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

void testAllowsRequestsWithinLimit() {
    RateLimiter limiter(3, std::chrono::seconds(10));

    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
}

void testRejectsRequestsOverLimit() {
    RateLimiter limiter(3, std::chrono::seconds(10));

    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == false);
}

void testDifferentKeysAreIndependent() {
    RateLimiter limiter(3, std::chrono::seconds(10));

    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == false);

    assert(limiter.allow("user2") == true);
}

void testAllowsAgainAfterWindow() {
    RateLimiter limiter(3, std::chrono::seconds(1));

    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == true);
    assert(limiter.allow("user1") == false);

    std::this_thread::sleep_for(std::chrono::milliseconds(1100));

    assert(limiter.allow("user1") == true);
}

int main() {
    testAllowsRequestsWithinLimit();
    testRejectsRequestsOverLimit();
    testDifferentKeysAreIndependent();
    testAllowsAgainAfterWindow();

    std::cout << "All tests passed!\n";
    return 0;
}