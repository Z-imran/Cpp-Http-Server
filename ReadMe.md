# 🛰️ Multithreaded HTTP Server in C++

This project implements a minimal **multithreaded HTTP/1.1 server** in C++ from scratch using POSIX sockets. It supports standard HTTP methods, concurrent client handling via a custom thread pool, and a fully testable interface using a Python testing script.

---

### Goals
- The goal of the project is to develop a deeper understanding of how servers actually work while also developing a deeper understanding of how C++ works. 
- Familiarize myself with a deeper understanding of internet sockets, and handling requests. 
- Use asynchronous programming to be able to handle multiple client requests at once. 
- Its also just a cool project. 


## 🚀 Features

- ✅ Serves static files over HTTP (`GET`)
- ✅ Handles `PUT`, `DELETE`, `HEAD`, and `OPTIONS` methods
- ✅ Parses valid HTTP/1.1 requests (method, headers, body)
- ✅ Sends proper status codes and headers (200, 404, 500, etc.)
- ✅ Asynchronous request handling via custom thread pool
- ✅ Basic MIME type detection
- ✅ Fully testable with built-in Python script and ApacheBench

---

## ⚙️ Technologies

- **C++17**
- **CMake** for build system
- **POSIX Sockets API**
- **Multithreading** (`std::thread`, `std::mutex`, `std::condition_variable`)

## 📊 Performance Benchmarks

Performance testing was done using [ApacheBench (ab)](https://httpd.apache.org/docs/2.4/programs/ab.html) on the `trial.html` file. Below are results for single, moderate, and high concurrency levels.

### 🔬 Test Setup
- **Machine**: Localhost (macOS, ARM64)
- **Server**: C++ HTTP server with custom thread pool (10 threads)
- **Client**: ApacheBench 2.3

---

### 🧪 Benchmark Results

| Test Case                     | Requests | Concurrency | Time Taken | Req/sec | Time/Req (ms) | Transfer Rate |
|------------------------------|----------|-------------|------------|---------|----------------|----------------|
| **Single Request**           | 1        | 1           | 0.001 sec  | 912.4   | 1.10           | 249 KB/s       |
| **Moderate Load**            | 100      | 10          | 0.016 sec  | 6,219   | 1.61           | 1700 KB/s      |
| **High Concurrency (Stress)**| 500      | 50          | 0.056 sec  | 8,906   | 5.61           | 2435 KB/s      |

---

### ⏱ Connection Time Breakdown (High Concurrency)

| Stage       | Min | Mean | Max |
|-------------|-----|------|-----|
| Connect     | 0ms | 0ms  | 2ms |
| Processing  | 1ms | 5ms  | 7ms |
| Total       | 3ms | 5ms  | 8ms |

---

### 📝 Observations

- ✅ The server handled 500 concurrent requests with **0 failures** and < 6ms mean processing time.
- ✅ Shows excellent scalability due to custom thread pool.
- ✅ Minimal connection latency with increasing load.


## Resources
Below are some resources used to help make programming easier. 
- https://man7.org/linux/man-pages/dir_section_2.html
- https://en.cppreference.com/w/cpp/header.html