#include "loader.h"

#include <QDebug>

#include "abstractaifactory.h"
#include "abstractaitransformer.h"

Loader::Loader()
    : m_loaded_rep(nullptr)
{

}

void Loader::updateAvailableReps()
{
    /*! \todo Fill in with initial list of representations */
}

bool Loader::loadRepresentation(const QString& rep, std::shared_ptr<AbstractRepSourceConfig> inputConfig)
{
    if (!m_available_reps.contains(rep)) {
        qDebug() << "Representation" << rep << "wasn't found";
        return false;
    }

    if (!inputConfig) {
        qDebug() << "Input config was null";
        return false;
    }

    unloadRepresentation();

    /*! \todo add call to actually load rep */

    auto transformer = m_available_reps.value(rep)->createTransformer();

    /*! \todo we could move the transformer to another thread to do the transformation */

    transformer->transform(inputConfig);
    if (transformer->hasError()) {
        qDebug() << "Transform error:" << transformer->getError().description();
        return false;
    }

    m_loaded_rep = transformer->getRepresentation();

    return true;
}

void Loader::unloadRepresentation()
{
    m_loaded_rep.reset();
}

