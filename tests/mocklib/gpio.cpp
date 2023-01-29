
#include "hardware/gpio.h"

#include "mock_gpio.h"

MockGpio mockGpio;

void gpio_init(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_init);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_init__gpio, gpio);
}

bool gpio_get(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_get);
    return mockGpio.getMethodReturnValue(MockGpioMethod__gpio_get);
}

void gpio_set_dir(uint gpio, bool out)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_set_dir);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_dir__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_dir__out, out);
}

void gpio_pull_down(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_pull_down);
}

void gpio_set_slew_rate(uint gpio, enum gpio_slew_rate slew)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_set_slew_rate);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_slew_rate__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_slew_rate__slew, slew);
}

void gpio_put(uint gpio, bool value)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_put);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_put__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_put__value, value);
}

// -----------------------------------
MockGpio::MockGpio()
{
}
MockGpio::~MockGpio()
{
}
void MockGpio::reset()
{
    this->methodCountCalls.clear();
    this->methodParameters.clear();
    this->methodReturnValue.clear();
}

void MockGpio::methodWasCalled(const MockGpioMethod method)
{
    this->methodCountCalls[method] = this->methodCountCalls[method] + 1;
}
void MockGpio::setParameter(const MockGpioMethodParameter parameter, int value)
{
    this->methodParameters[parameter] = value;
}

uint MockGpio::getParameter(const MockGpioMethodParameter parameter)
{
    return this->methodParameters[parameter];
}

int MockGpio::getCountMethodCalls(const MockGpioMethod method)
{
    return this->methodCountCalls[method];
}

void MockGpio::setMethodReturnValue(const MockGpioMethod method, int value)
{
    this->methodReturnValue[method] = value;
}

int MockGpio::getMethodReturnValue(const MockGpioMethod method)
{
    return this->methodReturnValue[method];
}
