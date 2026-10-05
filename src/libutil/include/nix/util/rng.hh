#pragma once
/*! \file
 *  \brief Psuedo-random number generators class for easier use of C++'s random number generation facilities.
 */

#include <random>
#include <limits>

namespace nix {

// Inspired by the book "A Tour of C++, Third Edition" (ISBN-10 0136816487)
template<typename T, typename Engine>
struct RandomNumberGenerator
{
public:
    using limits = std::numeric_limits<T>;
    using Distribution = std::conditional_t<
        std::is_floating_point_v<T>,
        std::uniform_real_distribution<T>,
        std::uniform_int_distribution<T>
    >;

    RandomNumberGenerator()
        : engine(std::random_device{}()){};

    RandomNumberGenerator(std::seed_seq seed)
        : engine(seed){};

    T operator()()
    {
        return Distribution{ limits::min(), limits::max() }(engine);
    }

    T operator()(T low, T high)
    {
        return Distribution{ low, high }(engine);
    }

    void seed(int s)
    {
        engine.seed(s);
    }
private:
    Engine engine;
};

} // namespace nix
