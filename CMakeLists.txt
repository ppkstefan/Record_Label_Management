cmake_minimum_required(VERSION 3.16)
project(EXAMENFINALSESIUNE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")


find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


include_directories(DOMAIN)
include_directories(GUI)
include_directories(REPO)
include_directories(SERVICE)


add_executable(EXAMENFINALSESIUNE
        DOMAIN/melodii.cpp
        DOMAIN/melodii.h
        GUI/MelodieTableModel.cpp
        GUI/MelodieTableModel.h
        GUI/MelodiiGUI.cpp
        GUI/MelodiiGUI.h
        REPO/melodiiRepo.cpp
        REPO/melodiiRepo.h
        SERVICE/melodiiService.cpp
        SERVICE/melodiiService.h
        main.cpp
        TESTE/teste.cpp
        TESTE/teste.h)

# Legam bibliotecile Qt de executabilul nostru
target_link_libraries(EXAMENFINALSESIUNE PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)