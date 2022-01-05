#ifndef RANDOM_LEVEL
#define RANDOM_LEVEL
#include "Level.h"
#include <unordered_map>
#include <random>

class RandomLevel :
    public Level
{
public:
    RandomLevel(std::unordered_map<char, double> probabilities);

    virtual Block current() const;

    virtual bool advanceNext();

    void setHeavy(bool enable);
private:
    void recalculateProbability();
    std::unordered_map<char, double> blockProbabilities_;
    Block currentBlock_;
    //sum of entries in blockProbabilities
    double sumProbabilities_;
    std::default_random_engine rng_;
    std::uniform_real_distribution<double> rngRange_;
    bool heavyEnabled_;
};
#endif
