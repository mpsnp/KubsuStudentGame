#ifndef _FUNC_DELEGATE_H
#define _FUNC_DELEGATE_H

#include "KSUEngine.h"
#include <vector>

typedef void (KSUCALL *TUFunction)(void *pParametr);

template <class T1>
class TempFunc {
    
    struct _TFunction
    {
        void *pParametr;
        T1 pFunction;
    };
    
    _TFunction _Function;
    
public:
    TempFunc()
    {
        DeleteFunction();
    }
    
    void PerformFunction()
    {
        _Function.pFunction(_Function.pParametr);
    }
    
    void AssignFunction(T1 pFunction, void *pParametr)
    {
        _Function.pParametr = pParametr;
        _Function.pFunction = pFunction;
    }
    
    void DeleteFunction()
    {
        _Function.pParametr = NULL;
        _Function.pFunction = NULL;
    }
    
    bool FunctionExists()
    {
        if (_Function.pFunction)
            return true;
        else
            return false;
    }
};

typedef TempFunc<TUFunction> TUserFunction;

#endif //_FUNC_DELEGATE_H
