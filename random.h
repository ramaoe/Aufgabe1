#ifndef RANDOM_H
#define RANDOM_H
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,9);
auto number = std::bind (distribution,generator);
#endif // RANDOM_H
