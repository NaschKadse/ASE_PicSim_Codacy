cmake_minimum_required(VERSION 3.17)
project(ASE_PicSim)

set(CMAKE_CXX_STANDARD 20)
if (WIN32)
    set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64")
    else()
    set(CMAKE_PREFIX_PATH "/Users/robin/Qt/5.15.2/clang_64/lib/cmake/Qt5")
endif ()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(CMAKE_OSX_ARCHITECTURES x86_64)

set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)



add_executable(ASE_PicSim src/main.cpp src/utility.cpp header/utility.h src/decode.cpp header/decode.h src/ram.cpp header/ram.h src/picSim.cpp header/picSim.h src/picsimgui.cpp header/picsimgui.h
        src/infodialog.cpp header/infodialog.h header/info.h src/info.cpp forms/info.ui src/picData.cpp header/picData.h src/movlw.cpp header/movlw.h src/rrf.cpp header/rrf.h src/rlf.cpp header/rlf.h src/andlw.cpp header/andlw.h src/iorlw.cpp header/iorlw.h src/sublw.cpp header/sublw.h src/xorlw.cpp header/xorlw.h src/addlw.cpp header/addlw.h src/cmdgo.cpp header/cmdgo.h src/cmdcall.cpp header/cmdcall.h src/customStack.cpp header/customStack.h src/cmdreturn.cpp header/cmdreturn.h src/retlw.cpp header/retlw.h src/retfie.cpp header/retfie.h src/nop.cpp header/nop.h src/movwf.cpp header/movwf.h src/addwf.cpp header/addwf.h src/andwf.cpp header/andwf.h src/clrf.cpp header/clrf.h src/comf.cpp header/comf.h src/decf.cpp header/decf.h src/incf.cpp header/incf.h src/movf.cpp header/movf.h src/clrw.cpp header/clrw.h src/iorwf.cpp header/iorwf.h src/xorwf.cpp header/xorwf.h src/subwf.cpp header/subwf.h src/swapf.cpp header/swapf.h src/incfsz.cpp header/incfsz.h src/decfsz.cpp header/decfsz.h src/bsf.cpp header/bsf.h src/bcf.cpp header/bcf.h src/btfsc.cpp header/btfsc.h src/btfss.cpp header/btfss.h src/command.cpp header/command.h src/LSTFileHandler.cpp header/LSTFileHandler.h src/readFileInterface.cpp header/readFileInterface.h src/handler.cpp header/handler.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
