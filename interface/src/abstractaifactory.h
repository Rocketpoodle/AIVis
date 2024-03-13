#ifndef ABSTRACTAIFACTORY_H
#define ABSTRACTAIFACTORY_H

#include <memory>
#include <string>

class AbstractAiTransformer;
class AbstractAiRepresentation;
class AbstractAiTransformer;

class AbstractAiFactory
{
public:
    AbstractAiFactory();

    virtual std::string getName() = 0;

    virtual std::unique_ptr<AbstractAiTransformer> createTransformer() = 0;

};

#endif // ABSTRACTAIFACTORY_H
