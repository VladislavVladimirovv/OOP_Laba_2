#include <iostream>
#include <iomanip>
#include "../include/octal.h"

int main()
{
    std::cout << std::boolalpha;

    std::cout << "========Демонстрация работы конструктора========\n"
              << std::endl;

    std::cout << "Создаём число num1" << std::endl;
    Octal num1;
    num1.print(std::cout) << std::endl;

    std::cout << "Создаём число num2 из 0" << std::endl;
    Octal num2(5, '0');
    num2.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создаём число num3 из списка инициализации" << std::endl;
    Octal num3({'1', '2', '3', '4'});
    num3.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создаём число num4 из строки" << std::endl;
    Octal num4("3425");
    num4.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создаём число num5, как копию числа num4" << std::endl;
    Octal num5(num4);
    std::cout << "Число num5 -> ";
    num5.print(std::cout) << std::endl;
    std::cout << "Число num4 -> ";
    num4.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создаём число num6, перемещая данные из чиса num5" << std::endl;
    Octal num6(std::move(num5));
    std::cout << "Число num6 после перемещения -> ";
    num6.print(std::cout) << std::endl;
    std::cout << "Число num5 после перемещения -> ";
    num5.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "========Работа с операциями========\n"
              << std::endl;
    std::cout << "Создадим число num7 как результат сложения восьмиричных чисел num3 и num4" << std::endl;
    Octal num7 = num3.add_assign(num4);
    std::cout << "Число num7 -> ";
    num7.print(std::cout) << std::endl;
    std::cout << "Число num3 -> ";
    num3.print(std::cout) << std::endl;
    std::cout << "Число num4 -> ";
    num4.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создадим число num8 как результат вычитания восьмиричных чисел num4 и num3" << std::endl;
    Octal num8 = num4.substruct_assign(num3);
    std::cout << "Число num8 -> ";
    num8.print(std::cout) << std::endl;
    std::cout << "Число num4 -> ";
    num4.print(std::cout) << std::endl;
    std::cout << "Число num3 -> ";
    num3.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "Создадим число num9 и скопируем в него число num8" << std::endl;
    Octal num9(num8.getSize(), '0');
    num9.copy(num8);
    std::cout << "Число num9 -> ";
    num9.print(std::cout) << std::endl;
    std::cout << "Число num8 -> ";
    num8.print(std::cout) << std::endl;
    std::cout << std::endl;

    std::cout << "========Демонстрация работы методов сравнения========\n"
              << std::endl;
    std::cout << "Проверим, что число num9 действительно равно числу num8 при помощи метода equals" << std::endl;
    std::cout << "Результат работы метода: " << num9.equals(num8) << std::endl;
    std::cout << std::endl;

    std::cout << "Проверим, что число num4 действительно больше числа num3 при помощи метода largest" << std::endl;
    std::cout << "Результат работы метода: " << num4.largest(num3) << std::endl;
    std::cout << std::endl;

    std::cout << "Проверим, что число num3 действительно меньше числа num4 при помощи метода smallest" << std::endl;
    std::cout << "Результат работы метода: " << num3.smallest(num4) << std::endl;
    std::cout << std::endl;

    std::cout << "Проверим, что число num3 действительно больше числа num4 при помощи метода smallest (Должно быть false, так как num3 < num4)" << std::endl;
    std::cout << "Результат работы метода: " << num3.largest(num4) << std::endl;
    std::cout << std::endl;

    std::cout << "========Демонстрация работы исключений========\n"
              << std::endl;
    try
    {
        std::cout << "Результат работы успешного вычитания из num4 - num3" << std::endl;
        Octal result1 = num4.substruct(num3);
        std::cout << "Результат -> ";
        result1.print(std::cout) << std::endl;
        std::cout << std::endl;

        std::cout << "Попытка вычесть из меньшего числа num3 большего числа num4 (Должно привести к ошибке)" << std::endl;
        Octal result2 = num3.substruct(num4);
        result2.print(std::cout) << std::endl;
    }
    catch (std::exception &exception)
    {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }

    std::cout << "\nВыход из main, вызов деструкторов" << std::endl;
    return 0;
}