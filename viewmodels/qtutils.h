#ifndef QTUTILS_H
#define QTUTILS_H

#include <QHash>
#include <QMetaEnum>
#include <QByteArray>

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

#endif // QTUTILS_H
