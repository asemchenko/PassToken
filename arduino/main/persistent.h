#ifndef PERSISTENT_H
#define PERSISTENT_H


#include <EEPROM.h>


template <typename T>
class PersistentScalar
{
public:
    PersistentScalar(size_t offset) : offset(offset)
    {
        EEPROM.get(offset, object);
    }

    PersistentScalar<T> & operator= (const PersistentScalar<T> &) = delete;

    const T& operator= (const T &value)
    {
        object = value;
        EEPROM.put(offset, object);
        return object;
    }

    operator T()
    {
        return object;
    }

private:
    T object;
    size_t offset;
};


template <typename T>
class PersistentArray
{
public:
    PersistentArray(size_t offset) : m_size(offset), offset(offset + sizeof(size_t)) {}
    
    PersistentScalar<T> operator[] (size_t index)
    {
        return PersistentScalar<T>(offset + sizeof(T) * index);
    }

    size_t size()
    {
        return m_size;
    }

    void append(const T &value)
    {
        PersistentScalar<T> scalar(offset + sizeof(T) * m_size);
        scalar = value;
        m_size = m_size + 1;
    }

    void erase()
    {
        m_size = 0;
    }

    void remove(size_t index)
    {
        m_size = m_size - 1;

        for (int i = index; i < m_size; ++i)
        {
            PersistentScalar<T> curr(offset + sizeof(T) * i);
            PersistentScalar<T> next(offset + sizeof(T) * (i + 1));

            curr = (T)next;
        }
    }

private:
    PersistentScalar<size_t> m_size;

    size_t offset;
};


#endif // PERSISTENT_H
