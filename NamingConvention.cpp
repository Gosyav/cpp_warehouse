#include <cmath>
#include <iostream>

class CartesianVectorClass
{
private:
    double x_{0.0};
    double y_{0.0};
    double z_{0.0};
    double normValue_{0.0};

public:
    CartesianVectorClass() = default;
    ~CartesianVectorClass() = default;

    void calculateNorm();
    double getNorm() { return normValue_; };
};

void CartesianVectorClass::calculateNorm()
{
    normValue_ = sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

struct ProgramSettingsStruct
{
    std::string dataPath{""};
    uint8_t numberOfIterations{2};
};

double convertStringToDouble(std::string number)
{
    return std::stod(number);
}

int main(int argc, const char **argv)
{
    uint32_t localVariable = 2;
    return 0;
}