    #include <iostream>
    #include <vector>
    #include <list>
    #include <chrono>
    #include <random>
    #include <format>
    #include <cassert>
    #include <algorithm>


    #if defined(_MSC_VER)      // Microsoft Visual C++
    #define NO_INLINE __declspec(noinline)
    #elif defined(__GNUC__) || defined(__clang__) // GCC or Clang
    #define NO_INLINE __attribute__((noinline))
    #elif defined(__INTEL_COMPILER) // Intel C/C++
    #define NO_INLINE __attribute__((noinline))
    #else
    #define NO_INLINE /* noinline not supported */
    #endif

    NO_INLINE void add(std::vector<int>& a, const std::vector<int>& b)
    {
        for (int i = 0; i < a.size(); i++) a[i] += b[i];
    }

    NO_INLINE void mult(std::vector<int>& a, const std::vector<int>& b)
    {
        for (int i = 0; i < a.size(); i++) a[i] *= b[i];
    }

    NO_INLINE void mult_add(std::vector<int>& a, const std::vector<int>& b, const std::vector<int>& c)
    {
        for (int i = 0; i < a.size(); i++) a[i] = a[i] * b[i] + c[i];
    }

    // Random number from 0 to max-1 inclusive
    int getRandomNum(int max)
    {
        static std::mt19937 engine{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(0, max - 1);
        return dist(engine);
    }

    template<class F>
    auto time_ns(F f, int N)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < N; i++) f();

        return std::chrono::high_resolution_clock::now() - start; 
    }

    int main(int argc, char* argv[]) {
        if (argc != 3) { throw std::runtime_error(std::format("Invalid command line arguments. Correct usage: {} <vector_size> <iteration_count>", argv[0])); }
        int vec_size = std::stoi(argv[1]);
        int iter_count = std::stoi(argv[2]); 
        std::vector<int> first(vec_size), second(vec_size), third(vec_size);
        std::vector<int> res;
        for(int i = 0; i < vec_size; i++) first [i] = getRandomNum(1000);
        for(int i = 0; i < vec_size; i++) second[i] = getRandomNum(1000);
        for(int i = 0; i < vec_size; i++) third[i] = getRandomNum(1000);

        volatile int x;

        auto separate_time = time_ns([&]()
            {
                mult(first, second);
                add(first, third);
                x += first[getRandomNum(first.size() - 1)];
            },
            iter_count
        );

        auto fused_time = time_ns([&]()
            { 
                mult_add(first, second, third);
                x += first[getRandomNum(first.size() - 1)];
            },
            iter_count
        );
        
        
        std::cout << std::format(
            "Time not fused: {:>7}\n"
            "Time     fused: {:>7}\n",
            std::chrono::duration_cast<std::chrono::milliseconds>(separate_time),
            std::chrono::duration_cast<std::chrono::milliseconds>(fused_time)
        );

        return 0;
    }
