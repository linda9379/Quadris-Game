#include "RandomLevel.h"
#include <random>

RandomLevel::RandomLevel(std::unordered_map<char, double> probabilities)
{
    blockProbabilities_ = probabilities;
    heavyEnabled_ = false;
    recalculateProbability();
}

Block RandomLevel::current() const
{
    return currentBlock_;
}

bool RandomLevel::advanceNext()
{
    //pick a random number in range [0,sum)
    double random = rngRange_(rng_);

    //each block is represented by a distinct interval within this range
    //the size of the interval is proportional to the probability of the block
    //we are checking which interval random lands within
    for (auto entry : blockProbabilities_) {
        if (random < entry.second) {
            currentBlock_ = Block::BlockMaker::makeBlock(entry.first, heavyEnabled_);
            return true;
        }
        else {
            random -= entry.second;
        }
    }
    //this should never run since probabilities sum to 1
    return false;
}

void RandomLevel::setHeavy(bool enable)
{
    heavyEnabled_ = enable;
}

void RandomLevel::recalculateProbability()
{
    sumProbabilities_ = 0;
    for (auto entry : blockProbabilities_) {
        sumProbabilities_ += entry.second;
    }
    rngRange_ = std::uniform_real_distribution<double>(0, sumProbabilities_);

}
