#pragma once

#include <chrono>
#include <random>

namespace ChunkMapEngine {
    /// Random provides a random number generator with range() functions for various data types.
    class Random
    {
    public:
        // seed
        inline static std::mt19937 randomNumberEngine{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

        inline static std::uniform_real_distribution<float> randomFloat{ FLT_MIN, FLT_MAX };
        inline static std::uniform_real_distribution<double> randomDouble{ DBL_MIN, DBL_MAX };
        inline static std::uniform_int_distribution<int> randomUChar{ 0, UCHAR_MAX };
        inline static std::uniform_int_distribution<int> randomInt{ INT_MIN, INT_MAX };

        static unsigned char nextUChar()
        {
            return static_cast<unsigned char>(randomUChar(randomNumberEngine));
        }

        static unsigned char uCharRange(unsigned char min, unsigned char max)
        {
            return static_cast<unsigned char>(std::uniform_int_distribution<int>{ min, max } (randomNumberEngine));
        }

        static int nextInt()
        {
            return randomInt(randomNumberEngine);
        }

        static int shortRange(short min, short max)
        {
            return std::uniform_int_distribution<short> { min, max } (randomNumberEngine);
        }

        static int intRange(int min, int max)
        {
            return std::uniform_int_distribution<int> { min, max } (randomNumberEngine);
        }

        static float nextFloat()
        {
            return randomFloat(randomNumberEngine);
        }

        static float floatRange(float min, float max)
        {
            return std::uniform_real_distribution<float> { min, max } (randomNumberEngine);
        }

        static double nextDouble()
        {
            return randomDouble(randomNumberEngine);
        }

        static double doubleRange(double min, double max)
        {
            return std::uniform_real_distribution<double> { min, max } (randomNumberEngine);
        }
    };
}