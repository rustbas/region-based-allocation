# TODO

- [x] Аллоцировать `char` или `u8`, так как их размер как раз 1 байт
- [x] Создать репозиторий
- [x] Свести все в STB-библиотеку
- [ ] Написать usage
- [ ] Написать примеры

# Description

STB-style library for Region-based memory management. 
Created for educational purposes.

# Usage

First of all, you need to initialize `region` 
(you may to redefine `REGION_SIZE`, default value is 2048 bytes):

```c
Region *region = regionInit(REGION_SIZE);
```

After that, you work with region like with default `malloc`:

```c
const size_t ROWS = 3;
const size_t COLS = 4;

double** matrix = regionAlloc(region, sizeof(double*)*ROWS);
for (size_t i = 0; i < ROWS; i++)
  matrix[i] = regionAlloc(region, sizeof(double)*COLS);
```

After all, you need to free region:

```c
regionFree(region);
```


# References 

- STB-style library: https://github.com/nothings/stb
- Region-based memory management: https://en.wikipedia.org/wiki/Region-based_memory_management
