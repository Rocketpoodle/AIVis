#ifndef ABSTRACTAITRANSFORMER_H
#define ABSTRACTAITRANSFORMER_H

#include <string>
#include <memory>

class AbstractRepSourceConfig;
class AbstractAiRepresentation;

class TransformError
{
public:
    enum ErrorCode {
        None=0,
    };
    TransformError() : m_code(None) {};

    TransformError(ErrorCode code, const std::string& description = "")
        : m_code(code)
        , m_description(description) {}

    ErrorCode code() const { return m_code; }
    std::string description() const { return m_description; }

private:
    ErrorCode m_code;
    std::string m_description;
};

class AbstractAiTransformer
{
public:
    AbstractAiTransformer();

    virtual void transform(std::shared_ptr<AbstractRepSourceConfig> inputConfig) = 0;

    bool hasError() const { return m_error.code() == TransformError::None; }
    const TransformError& getError() const { return m_error; }

    bool done() const;
    std::shared_ptr<AbstractAiRepresentation> getRepresentation() const { return m_representation; }

protected:
    TransformError m_error;
    std::shared_ptr<AbstractAiRepresentation> m_representation;
};


#endif // ABSTRACTAITRANSFORMER_H
