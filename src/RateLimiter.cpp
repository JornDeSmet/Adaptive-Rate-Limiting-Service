#include "RateLimiter.h"
#include <algorithm>


RateLimiter::RateLimiter(std::size_t allowedRequests, std::chrono::seconds timeWindow) 
: allowedRequests(allowedRequests), timeWindow(timeWindow) {}



bool RateLimiter::allow(const std::string& key){
    std::lock_guard<std::mutex> lock(mtx);
    
    auto now = std::chrono::steady_clock::now();
    RateLimiter::cleanUp(now);
    auto& request = history[key];

    while(!request.empty() && request.front() <= now - timeWindow){
        request.pop_front();
    }

    if(request.size() >= allowedRequests){
        return false;
    }

    request.push_back(now);

    return true;

}

void RateLimiter::cleanUp(const std::chrono::steady_clock::time_point& now) {
    const auto cutoff = now - timeWindow;

    std::erase_if(history, [&](const auto& entry) {
        const auto& requests = entry.second;
        return requests.empty() || requests.back() <= cutoff;
    });
}