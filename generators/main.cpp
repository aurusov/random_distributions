#include <iostream>
#include <cstdint>
#include <math.h>

class Generator
{
protected:
    Generator(std::uint32_t a_seed)
    {
        seed_ = a_seed;
    }

    double next_u01()
    {
        return next_seed() / 4294967296.0;
    }

private:
    std::uint32_t seed_;

    std::uint32_t next_seed()
    {
        seed_ = seed_ * 69069 + 1;
        return seed_;
    }
};

class Uniform: public Generator
{
public:
    Uniform(std::uint32_t a_seed, double a, double b)
        : Generator(a_seed)
    {
        a_ = a;
        b_ = b;
    }

    double next_value()
    {
        return a_ + next_u01() * (b_ - a_);
    }

private:
    double a_;
    double b_;
};

class Exponential: public Generator
{
public:
    Exponential(std::uint32_t a_seed, double mean)
        : Generator(a_seed)
    {
        mean_ = mean;
    }

    double next_value()
    {
        return -log(next_u01()) * mean_;
    }

private:
    double mean_;
};

class Normal: public Generator
{
public:
    Normal(std::uint32_t a_seed, double mean, double std_dev)
        : Generator(a_seed)
    {
        mean_ = mean;
        std_dev_ = std_dev;
    }

    double next_value()
    {
        double sum = 0;
        for (std::size_t i = 0; i < 12; ++i)
        {
            sum += next_u01();
        }
        return std_dev_ * (sum - 6) + mean_;
    }

private:
    double mean_;
    double std_dev_;
};

template<class T>
void print(T sequence)
{
    const std::size_t count = 10;
    for (std::size_t i = 0; i < count; ++i)
        std::cout << i << ". " << sequence.next_value() << std::endl;
}

int main()
{
    std::cout << "uniform" << std::endl;
    Uniform uniform(12345, 1.5, 4.3);
    print(uniform);

    std::cout << std::endl;
    std::cout << "exponential" << std::endl;
    Exponential exponential(12345, 14.2);
    print(exponential);

    std::cout << std::endl;
    std::cout << "normal" << std::endl;
    Normal normal(12345, 15.2, 0.4);
    print(normal);

    return 0;
}
