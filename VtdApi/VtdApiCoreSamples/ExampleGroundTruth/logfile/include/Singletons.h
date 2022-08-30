#ifndef  _SINGLETONS_H
#define  _SINGLETONS_H

/**
 *  - Singelton class
 */
template <class T>
class Singletons
{
public:
    /**
     * @brief Singletons - constructor
     */
	Singletons(){}

    /**
     * @brief ~Singletons - destructor
     */
    virtual ~Singletons(){}

protected:

    /**
     * @brief pointSingleton - static Object
     */
    static T *pointSingleton;

public:

    /**
     * @brief Get - get object instance
     * @return instance
     */
	inline static T* Get()
	{
		if (!pointSingleton)
		{
			pointSingleton = new T;
		}

		return pointSingleton;
	}

    /**
     * @brief Del - delete object instance
     */
	static void Del()
	{
        if (!pointSingleton)
		{
			delete pointSingleton;
            pointSingleton = NULL;
		}
	}
};

template<class T>
T* Singletons<T>::pointSingleton = 0;

#endif //_SINGLETONS
