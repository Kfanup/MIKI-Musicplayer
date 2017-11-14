#pragma once

namespace MMusic {
extern QString filePathToHash(const QString &filePath);
extern QString length2String(const qint64 length);

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
