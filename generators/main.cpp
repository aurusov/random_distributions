#include <cstdint>
#include <iostream>
#include <limits>
#include <math.h>

class Generator
{
protected:
    Generator(std::uint32_t seed_)
    {
        seed = seed_;
    }

    double next_u01()
    {
        const double values_count = std::numeric_limits<std::uint32_t>::max() + 1.0;
        return next_seed() / values_count;
    }

private:
    std::uint32_t seed;

    std::uint32_t next_seed()
    {
        seed = seed * 69069 + 1;
        return seed;
    }
};

class Uniform: public Generator
{
public:
    Uniform(std::uint32_t seed_, double min_, double max_)
        : Generator(seed_)
    {
        min = min_;
        max = max_;
    }

    double next_value()
    {
        return min + next_u01() * (max - min);
    }

private:
    double min;
    double max;
};

class Exponential: public Generator
{
public:
    Exponential(std::uint32_t seed_, double mean_)
        : Generator(seed_)
    {
        mean = mean_;
    }

    double next_value()
    {
        return -log(next_u01()) * mean;
    }

private:
    double mean;
};

class Normal: public Generator
{
public:
    Normal(std::uint32_t seed_, double mean_, double std_dev_)
        : Generator(seed_)
    {
        mean = mean_;
        std_dev = std_dev_;
    }

    double next_value()
    {
        double sum = 0;
        for (std::size_t i = 0; i < 12; ++i)
            sum += next_u01();

        return std_dev * (sum - 6) + mean;
    }

private:
    double mean;
    double std_dev;
};

template<class T>
void print_values(T & sequence)
{
    const std::size_t count = 10;
    for (std::size_t i = 0; i < count; ++i)
        std::cout << i << ". " << sequence.next_value() << std::endl;
}

int main()
{
    std::cout << "uniform" << std::endl;
    Uniform uniform(12345, 1.5, 4.3);
    print_values(uniform);

    std::cout << std::endl;
    std::cout << "exponential" << std::endl;
    Exponential exponential(12345, 14.2);
    print_values(exponential);

    std::cout << std::endl;
    std::cout << "normal" << std::endl;
    Normal normal(12345, 15.2, 0.4);
    print_values(normal);

    return 0;
}
