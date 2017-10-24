#pragma once

namespace MMusic {
QString filePathToHash(const QString &filePath);

template <class T>
class MSingleTon
{
public:
    static inline T *instance()
    {
        static T *_instance = new T;
        return _instance;
    }

protected:
    MSingleTon() {}
    ~MSingleTon() {}
    MSingleTon(const MSingleTon &) {}
    MSingleTon &operator=(const MSingleTon &) { return *this; }
};
}
