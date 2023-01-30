#ifndef BASE_MOCK__H
#define BASE_MOCK__H

#include <stdint.h>
#include <map>

template <typename METHOD, typename PARAM>
class BaseMock
{
private:
    std::map<METHOD, int> methodCountCalls;
    std::map<PARAM, uintptr_t> methodParameters;
    std::map<METHOD, uintptr_t> methodReturnValue;

public:
    virtual void reset()
    {
        this->methodCountCalls.clear();
        this->methodParameters.clear();
        this->methodReturnValue.clear();
    }

    virtual void methodWasCalled(const METHOD method)
    {
        this->methodCountCalls[method] = this->methodCountCalls[method] + 1;
    }

    virtual void setMethodReturnValue(const METHOD method, uintptr_t value)
    {
        this->methodReturnValue[method] = value;
    }

    virtual uintptr_t getMethodReturnValue(const METHOD method)
    {
        return this->methodReturnValue[method];
    }

    virtual void setParameter(const PARAM parameter, uintptr_t value)
    {
        this->methodParameters[parameter] = value;
    }

    virtual uintptr_t getParameter(const PARAM parameter)
    {
        return this->methodParameters[parameter];
    }

    int getCountMethodCalls(const METHOD method)
    {
        return this->methodCountCalls[method];
    }
};

#endif
