#ifndef OCTAL_H
#define OCTAL_H

#include <string>
#include <initializer_list>
#include <iostream>

class Octal
{
public:
    Octal();
    Octal(const size_t &n, unsigned char t);
    Octal(const std::initializer_list<unsigned char> &t);
    Octal(const std::string &t);

    Octal(const Octal &other);
    Octal(Octal &&other) noexcept;

    Octal add(const Octal &other);
    Octal substruct(const Octal &other);
    Octal copy(const Octal &other);
    Octal add_assign(const Octal &other);
    Octal substruct_assign(const Octal &other);

    bool equals(const Octal &Object) const;
    bool largest(const Octal &other) const;
    bool smallest(const Octal &other) const;

    int translation() const;
    size_t getSize();
    std::ostream &print(std::ostream &outputStream);

    virtual ~Octal() noexcept;

private:
    size_t octalSize{0};
    unsigned char *dataOctal{nullptr};
};

#endif