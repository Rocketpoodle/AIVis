#ifndef LOADER_H
#define LOADER_H

#include <memory>
#include <QHash>
#include <QString>
#include <QList>

class AbstractAiFactory;
class AbstractAiRepresentation;
class AbstractRepSourceConfig;

class Loader
{
public:
    Loader();

    void updateAvailableReps();

    QList<QString> getRepNames() const { return m_available_reps.keys(); };

    bool loadRepresentation(const QString& rep, std::shared_ptr<AbstractRepSourceConfig> inputConfig);
    void unloadRepresentation();

    std::shared_ptr<AbstractAiRepresentation> getLoadedRep() const { return m_loaded_rep; }

private:
    QHash<QString, std::shared_ptr<AbstractAiFactory>> m_available_reps;

    std::shared_ptr<AbstractAiRepresentation> m_loaded_rep;
};

#endif // LOADER_H
