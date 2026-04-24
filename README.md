# Adaptive Rate Limiting Service

A small C++ rate limiter using a sliding window algorithm.

## Design choices

- Uses a sliding window per key.
- Each key stores recent request timestamps.
- Old timestamps are removed when checking a key.
- Access is protected with a mutex, making it thread-safe inside one process.
- Configuration is passed through the constructor.

## Assumptions

- The limiter runs inside a single service process.
- All the data gets saved in RAM so once u restart the process its gone.

## Usage

```cpp
#include "RateLimiter.h"

RateLimiter limiter(3, std::chrono::seconds(10));

if (limiter.allow("user-123")) {
    // request allowed
} else {
    // request rejected
}

```

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run Demo

```bash
./main
```

## Run Tests

```bash
./rate_limiter_tests
```
