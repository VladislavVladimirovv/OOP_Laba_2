#include <iostream>
#include "../include/octal.h"

Octal::Octal() : octalSize(0), dataOctal(nullptr)
{
}

Octal::Octal(const size_t &n, unsigned char t)
{
    this->octalSize = n;
    this->dataOctal = new unsigned char[this->octalSize];

    for (size_t i{this->octalSize}; i > 0; --i)
        this->dataOctal[i - 1] = t;
}

Octal::Octal(const std::initializer_list<unsigned char> &t)
{
    this->octalSize = t.size();
    this->dataOctal = new unsigned char[this->octalSize];

    size_t i{octalSize};
    for (const auto &value : t)
    {
        this->dataOctal[i - 1] = value;
        i--;
    }
}

Octal::Octal(const std::string &t)
{
    this->octalSize = t.size();
    this->dataOctal = new unsigned char[octalSize];

    for (size_t i{this->octalSize}; i > 0; i--)
        this->dataOctal[i - 1] = static_cast<unsigned char>(t[octalSize - i]);
}

Octal::Octal(const Octal &other)
{
    this->octalSize = other.octalSize;
    this->dataOctal = new unsigned char[octalSize];

    for (size_t i = 0; i < this->octalSize; ++i)
        this->dataOctal[i] = other.dataOctal[i];
}

Octal::Octal(Octal &&other) noexcept
{

    this->octalSize = other.octalSize;
    this->dataOctal = other.dataOctal;

    other.octalSize = 0;
    other.dataOctal = nullptr;
}

Octal Octal::add(const Octal &other)
{

    size_t max_size{0};

    if (this->octalSize >= other.octalSize)
    {
        max_size = this->octalSize;
    }
    else
    {
        max_size = other.octalSize;
    }

    Octal oct(max_size + 1, '0');

    int dig1{0};
    int dig2{0};
    int ost{0};
    for (size_t i{0}; i < oct.octalSize; ++i)
    {
        dig1 = (this->octalSize > i) ? this->dataOctal[i] - '0' : 0;
        dig2 = (other.octalSize > i) ? other.dataOctal[i] - '0' : 0;
        oct.dataOctal[i] = ((dig1 + dig2 + ost) % 8) + '0';
        ost = (dig1 + dig2 + ost) / 8;
    }

    if (oct.dataOctal[oct.octalSize - 1] == '0')
    {
        oct.octalSize--;
    }
    return oct;
}

Octal Octal::substruct(const Octal &other)
{
    if (this->smallest(other))
        throw std::invalid_argument("ОШИБКА: Первое число меньше второго");
    else if (this->equals(other))
    {
        Octal oct(1, '0');
        return oct;
    }
    Octal oct(this->octalSize, '0');
    int dig1{0};
    int dig2{0};
    int ceil{0};
    for (size_t i{0}; i < oct.octalSize; i++)
    {
        dig1 = (this->octalSize > i) ? (this->dataOctal[i] - '0') - ceil : 0;
        dig2 = (other.octalSize > i) ? other.dataOctal[i] - '0' : 0;
        if (dig1 < dig2)
        {
            dig1 += 8;
            ceil = 1;
        }
        else
        {
            ceil = 0;
        }
        oct.dataOctal[i] = (dig1 - dig2) + '0';
    }
    for (size_t i{oct.octalSize}; i > 0; i--)
        if (oct.dataOctal[i - 1] != '0')
        {
            oct.octalSize = i;
            break;
        }
    return oct;
}

Octal Octal::add_assign(const Octal &other)
{
    return this->add(other);
}

Octal Octal::substruct_assign(const Octal &other)
{
    return this->substruct(other);
}

Octal Octal::copy(const Octal &other)
{
    if (this == &other)
        return *this;
    if (this->octalSize != other.octalSize)
        throw std::invalid_argument("ОШИБКА: Несовпадение длин чисел");
    for (size_t i{0}; i < this->octalSize; i++)
        this->dataOctal[i] = other.dataOctal[i];
    return *this;
}

bool Octal::equals(const Octal &other) const
{
    if (this->octalSize != other.octalSize)
        return false;
    if (this->translation() == other.translation())
        return true;
    return false;
}

bool Octal::largest(const Octal &other) const
{
    if (this->octalSize < other.octalSize)
        return false;
    if ((this->octalSize > other.octalSize) || (this->translation() > other.translation()))
        return true;
    return false;
}

bool Octal::smallest(const Octal &other) const
{
    if (this->octalSize > other.octalSize)
        return false;
    if ((this->octalSize < other.octalSize) || (this->translation() < other.translation()))
        return true;
    return false;
}

int Octal::translation() const
{
    int number{0};
    for (size_t i{this->octalSize}; i > 0; --i)
        number = number * 10 + this->dataOctal[i - 1];
    return number;
}

size_t Octal::getSize()
{
    return this->octalSize;
}

std::ostream &Octal::print(std::ostream &outputStream)
{
    for (size_t i{this->octalSize}; i > 0; --i)
        outputStream << this->dataOctal[i - 1];
    return outputStream;
}

Octal::~Octal() noexcept
{
    if (this->dataOctal != nullptr)
    {
        delete[] this->dataOctal;
        this->dataOctal = nullptr;
    }
    this->octalSize = 0;
}
