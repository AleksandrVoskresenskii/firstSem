cmake_minimum_required(VERSION 3.10)
project(MyProject C)  # Или CXX, если пишете на C++

# Указываем стандарт языка, например, C99:
set(CMAKE_C_STANDARD 99)

# Собираем исполняемый файл myapp из перечисленных .c-файлов
add_executable(myapp
    main.c
    tree.c
)