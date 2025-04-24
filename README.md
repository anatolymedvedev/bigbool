# Bigbool
Bigbool - библиотека на языке *С*, позволяющая создавать булевы вектора произвольный длины и проводить логические операции над ними. Порядок байтов - *little-endian*.
## Использование   
*Конструкторы:*  
#### `BB_from_string(char* str)`  
Преобразует строку в вектор  
#### `char* BB_to_str(bigbool* vec)`  
Создает строку из вектора  
#### `BB_from_uint64(uint64_t num)`  
Преобразует 64-битное число в вектор  

Примеры:  

```  
bigbool* vec = BB_from_string("10110111");           //bigbool vec is created with value 10110111.  
char* string = BB_to_str(vec);                       //string is created with value 10110111.
uint64_t num = 8192;
bigbool* vec = BB_from_uint64(num);                  //bigbool vec is created with value 10000000000000.
uint64_t num1 = 0b101111011111001000100010110100101;
bigbool* vec = BB_from_uint64(num1);                 //bigbool vec is created with value 101111011111001000100010110100101.
```  
## Методы  
#### `len_vector(bigbool* vec)`  
Считает длину вектора в битах  
#### `empty_bool(size_t len)`  
Создает пустой вектор и зануляет его  
#### `equil_size(bigbool* vec1, bigbool* vec2)`  
Делает вектора равной длины  
#### `BB_not(bigbool* vec)`  
Вычисляет инверсию вектора  
#### `BB_xor(bigbool* vec1, bigbool* vec2)`  
Вычисляет ксор двух векторов  
#### `BB_or(bigbool* vec1, bigbool* vec2)`  
Вычисляет дизъюнкцию двух векторов  
#### `BB_and(bigbool* vec1, bigbool* vec2)`  
Вычисляет конъюнкцию двух векторов  
#### `BB_left_shift(bigbool* vec, int num)`  
Сдвигает вектор влево (делая его больше)  
#### `BB_right_shift(bigbool* vec, int num)`  
Сдвигает вектор вправо (делая его меньше)  
#### `BB_left_circle_shift(bigbool* vec, int num)`  
Циклически сдвигает вектор влево (получаемый вектор остаётся той же длины, что и передаваемый)  
#### `BB_right_circle_shift(bigbool* vec, int num)`  
Циклически сдвигает вектор вправо (получаемый вектор остаётся той же длины, что и передаваемый)  
#### `BB_free(bigbool* vec)`  
Очищает выделенную память на куче для вектора  
## Тесты
В файлах [test.c](https://github.com/anatolymedvedev/bigbool/blob/main/test.c) и [xor.c](https://github.com/anatolymedvedev/bigbool/blob/main/xor.c) приведены тесты всех функций.
