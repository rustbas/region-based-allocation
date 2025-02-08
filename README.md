# TODO

- [x] Alloc only chars or u8
- [x] Create STB-style header file
- [x] Write usage
- [x] Create examples
- [ ] Create 'stack' version (optional)

# Description

STB-style library for Region-based memory management. 
Created for educational purposes.

# Usage

> You can download repository and run `make demo`. 
> Is repeats the following information.

First of all, you need to initialize `region` 
(you may want to redefine `REGION_SIZE`, default value is 2048 bytes):

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

For debug purposes you can print region information:

```c
regionDump(region);
```

It prints all information about region.

# References 

- STB-style library: https://github.com/nothings/stb
- Region-based memory management: https://en.wikipedia.org/wiki/Region-based_memory_management
