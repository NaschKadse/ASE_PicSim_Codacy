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



add_executable(ASE_PicSim src/4_Main/main.cpp src/2_Application_Code/utility.cpp header/utility.h src/2_Application_Code/decode.cpp header/decode.h src/0_Abstraction_Code/ram.cpp header/ram.h src/2_Application_Code/picSim.cpp header/picSim.h src/3_Plugins/picsimgui.cpp header/picsimgui.h
        src/3_Plugins/infodialog.cpp header/infodialog.h header/info.h src/3_Plugins/info.cpp forms/info.ui src/0_Abstraction_Code/picData.cpp header/picData.h src/1_Domain_Code/movlw.cpp header/movlw.h src/1_Domain_Code/rrf.cpp header/rrf.h src/1_Domain_Code/rlf.cpp header/rlf.h src/1_Domain_Code/andlw.cpp header/andlw.h src/1_Domain_Code/iorlw.cpp header/iorlw.h src/1_Domain_Code/sublw.cpp header/sublw.h src/1_Domain_Code/xorlw.cpp header/xorlw.h src/1_Domain_Code/addlw.cpp header/addlw.h src/1_Domain_Code/cmdgo.cpp header/cmdgo.h src/1_Domain_Code/cmdcall.cpp header/cmdcall.h src/0_Abstraction_Code/customStack.cpp header/customStack.h src/1_Domain_Code/cmdreturn.cpp header/cmdreturn.h src/1_Domain_Code/retlw.cpp header/retlw.h src/1_Domain_Code/retfie.cpp header/retfie.h src/1_Domain_Code/nop.cpp header/nop.h src/1_Domain_Code/movwf.cpp header/movwf.h src/1_Domain_Code/addwf.cpp header/addwf.h src/1_Domain_Code/andwf.cpp header/andwf.h src/1_Domain_Code/clrf.cpp header/clrf.h src/1_Domain_Code/comf.cpp header/comf.h src/1_Domain_Code/decf.cpp header/decf.h src/1_Domain_Code/incf.cpp header/incf.h src/1_Domain_Code/movf.cpp header/movf.h src/1_Domain_Code/clrw.cpp header/clrw.h src/1_Domain_Code/iorwf.cpp header/iorwf.h src/1_Domain_Code/xorwf.cpp header/xorwf.h src/1_Domain_Code/subwf.cpp header/subwf.h src/1_Domain_Code/swapf.cpp header/swapf.h src/1_Domain_Code/incfsz.cpp header/incfsz.h src/1_Domain_Code/decfsz.cpp header/decfsz.h src/1_Domain_Code/bsf.cpp header/bsf.h src/1_Domain_Code/bcf.cpp header/bcf.h src/1_Domain_Code/btfsc.cpp header/btfsc.h src/1_Domain_Code/btfss.cpp header/btfss.h src/1_Domain_Code/command.cpp header/command.h src/3_Plugins/LSTFileHandler.cpp header/LSTFileHandler.h header/readFileInterface.h src/2_Application_Code/handler.cpp header/handler.h)

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
