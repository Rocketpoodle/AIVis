#ifndef UTILS_H
#define UTILS_H

template <class T> class GenericSingleton
{
public:
    static T& instance() {
        static T singleton_obj;
        return singleton_obj;
    }

protected:
    GenericSingleton() {};
    ~GenericSingleton() {};
};

#define CREATE_SINGLETON(UnderlyingType, SingletonAlias) \
using SingletonAlias = GenericSingleton<UnderlyingType>;

#endif // UTILS_H
