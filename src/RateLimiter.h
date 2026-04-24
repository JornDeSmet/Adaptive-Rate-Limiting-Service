#pragma once


#include <mutex>
#include <string>
#include <unordered_map>
#include <deque>
#include <chrono>



class RateLimiter {
    private:
        std::unordered_map<std::string, std::deque<std::chrono::steady_clock::time_point>> history;
        mutable std::mutex mtx;

        std::size_t allowedRequests;
        std::chrono::seconds timeWindow;

    public:
        bool allow(const std::string& key);


        RateLimiter(std::size_t allowedRequests, std::chrono::seconds timeWindow);

};