#ifndef QTUTILS_H
#define QTUTILS_H

#include <QHash>
#include <QMetaEnum>
#include <QByteArray>
#include <QQmlEngine>

template <class EnumType> QHash<int, QByteArray> getRoleNamesFromEnum()
{
    auto roles = QMetaEnum::fromType<EnumType>();
    QHash<int, QByteArray> rolesMap;
    for (int i=0; i < roles.keyCount(); ++i) {
        rolesMap.insert(roles.value(i), roles.key(i));
    }
    return rolesMap;
}

#define ASSIGN_ROLES(RolesEnumType) \
    /*! \macro Macro to set enum as QML roles for item model. Must be in public section of QAbstractItemModel subclass */ \
    public: \
        Q_ENUM(RolesEnumType); \
        QHash<int, QByteArray> roleNames() const override {return m_roleNamesHash;}; \
    private: \
        QHash<int, QByteArray> m_roleNamesHash = getRoleNamesFromEnum<RolesEnumType>(); \
    public:

template <class T>
/*!
 * \brief The CppQmlSingleton class
 * Template class for QML singletons
 */
class CppQmlSingleton
{
public:
    static T& instance() {
        static T singleton_obj;
        return singleton_obj;
    }

    static T* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
        QQmlEngine::setObjectOwnership(&T::instance(), QQmlEngine::CppOwnership);
        return &T::instance();
    }

protected:
    CppQmlSingleton() {};
    ~CppQmlSingleton() {};
};

#define DEFINE_QML_SINGLETON(UnderlyingType, SingletonAlias) \
/*!
 * \brief The SingletonAlias class
 * Macro to create a QML Singleton from the type given for "UnderlyingType"
 * and named by the value given for "SingletinAlias". Underlying type
 * must be a subclass of QObject in some form.
 */ \
class SingletonAlias : public UnderlyingType, public CppQmlSingleton<SingletonAlias> \
{ \
    Q_OBJECT \
    QML_ELEMENT \
    QML_SINGLETON \
protected: \
    SingletonAlias() {}; \
    ~SingletonAlias() {}; \
private: \
friend CppQmlSingleton<SingletonAlias>; \
};

#endif // QTUTILS_H
