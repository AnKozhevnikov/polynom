# Библиотека polynom.hpp

## Описание
Данная библиотека предоставляет пользователю класс Polynom, объявленный в файле polygon.hpp, который умеет работать с многочленами от нескольких переменных, выполнять над ними математические операции, а также вычислять значение, подставляя значения в переменные.

Коэфициентами при членах, а также подставляемые значения могут быть представлены любыми типами, как стандартными, так и пользовательскими. На пользовательские коэфициенты и подставляемые значения накладываются некоторые ограничения, но об этом позднее.

Степени при переменных это беззнаковые целые числа.

## Использование

### Инициализация

Polynom представляет из себя шаблонный класс, где шаблонным типом является коэфициент при членах, который нужно указать при инициализации многочлена.
```cpp
Polygon<int> p;
```
Конструктор по умолчанию создаст нулевой многочлен.

Задать многочлен можно также и через строку. Строка должна состоять из членов, разделенных знаками + и -. Каждый член имеет вид [коэфициент]буква^степень*буква^степень... Допускается использование одной буквы более одного раза, а также переменной в первой степени, после которой можно не писать ^1, а также не писать символ *.

Здесь есть тонкость. Так как класс может не знать как создать например пользовательский коэфициент из строки, а также как он выглядит здесь накладываются два ограничения.

1) Вместе со строкой в конструктор передаётся и функция, принимающая на вход std::string, с возвращаемым типом коэфициента. Для базовых типов уже заготовлены функции, находящиеся в пространстве имён pconverter
2) Так как класс не знает, как выглядит коэфициент, ему нужно как то указать на его границы. Именно поэтому все коэфициенты необходимо оборачивать в квадратные скобки, даже если это свободный член.

Пример инициализации многочлена из строки:
```cpp
Polygon<int> p("[5]x^2*y-[2]xyx-[6]", pconverter::to_int);
```

Также константный многочлен можно задать, как
```cpp
Polygon<double> p(10.5);
```

Внутри класса многочлен представлен, как
```cpp
std::map<std::map<char, unsigned int>, T>
```
Предусмотрена возможность задания многочлена через данную структуру данных

### Арифмитеческие операции

Над многочленом можно проводить различные арифмитические операции, а именно

1) Сложение
2) Вычитание
3) Умножение
4) Возведение в целую неотрицательную
5) Унарный минус
6) Прибавление и вычитание константы
7) Умножение на константу
8) Унарный минус

### Исполнение

Класс Polynom содержит метод apply, который подставляет в буквы значение и возвращает результат. Его сигнатура выглядит следующим образом:
```cpp
template <typename U>
U apply(std::map<char, U> m) const;
```

Применение выглядит, как:
```cpp
int ans = p1.apply(std::map<char, int>{
        {'x', 2},
        {'y', 3}
    });
```

### Ограничения

Коэфициенты и подставляемые значения должны представлять собой линейное пространство. В частности, конструктор по умолчанию от типа коэфициента должен возвращать "ноль", а конструктор вида T(1) от типа подставляемого значения должен возвращать "единицу".