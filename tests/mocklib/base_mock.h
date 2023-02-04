/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2023 Slava Zanko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
