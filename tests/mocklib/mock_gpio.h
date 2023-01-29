#ifndef MOCK_GPIO__H
#define MOCK_GPIO__H

#include <map>

typedef enum
{
    MockGpioMethod__gpio_init,
    MockGpioMethod__gpio_get,
    MockGpioMethod__gpio_set_dir,
    MockGpioMethod__gpio_pull_down,
    MockGpioMethod__gpio_set_slew_rate,
    MockGpioMethod__gpio_put,
} MockGpioMethod;

typedef enum
{
    MockGpioMethodParameter__gpio_init__gpio,
    MockGpioMethodParameter__gpio_set_dir__gpio,
    MockGpioMethodParameter__gpio_set_dir__out,
    MockGpioMethodParameter__gpio_set_slew_rate__gpio,
    MockGpioMethodParameter__gpio_set_slew_rate__slew,
    MockGpioMethodParameter__gpio_put__gpio,
    MockGpioMethodParameter__gpio_put__value,
} MockGpioMethodParameter;

class MockGpio
{
private:
    std::map<MockGpioMethod, int> methodCountCalls;
    std::map<MockGpioMethodParameter, int> methodParameters;
    std::map<MockGpioMethod, int> methodReturnValue;

public:
    MockGpio();
    virtual ~MockGpio();
    void reset();

    void methodWasCalled(const MockGpioMethod);

    void setMethodReturnValue(const MockGpioMethod, int);
    int getMethodReturnValue(const MockGpioMethod);

    void setParameter(const MockGpioMethodParameter, int);

    uint getParameter(const MockGpioMethodParameter);

    int getCountMethodCalls(const MockGpioMethod);
};

extern MockGpio mockGpio;

#endif
