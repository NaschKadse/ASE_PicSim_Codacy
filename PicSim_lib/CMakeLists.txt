project(PicSim_lib)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)


set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64")
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets PicSim_lib)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(PicSim_lib
        0_Abstraction_Code/customStack.h
        0_Abstraction_Code/picData.h
        0_Abstraction_Code/ram.h
        1_Domain_Code/addlw.h
        1_Domain_Code/addwf.h
        1_Domain_Code/andlw.h
        1_Domain_Code/andwf.h
        1_Domain_Code/bcf.h
        1_Domain_Code/bsf.h
        1_Domain_Code/btfsc.h
        1_Domain_Code/btfss.h
        1_Domain_Code/clrf.h
        1_Domain_Code/clrw.h
        1_Domain_Code/cmdcall.h
        1_Domain_Code/cmdgo.h
        1_Domain_Code/cmdreturn.h
        1_Domain_Code/comf.h
        1_Domain_Code/command.h
        1_Domain_Code/decf.h
        1_Domain_Code/decfsz.h
        1_Domain_Code/incf.h
        1_Domain_Code/incfsz.h
        1_Domain_Code/iorlw.h
        1_Domain_Code/iorwf.h
        1_Domain_Code/movf.h
        1_Domain_Code/movlw.h
        1_Domain_Code/movwf.h
        1_Domain_Code/nop.h
        1_Domain_Code/retfie.h
        1_Domain_Code/retlw.h
        1_Domain_Code/rlf.h
        1_Domain_Code/rrf.h
        1_Domain_Code/sublw.h
        1_Domain_Code/subwf.h
        1_Domain_Code/swapf.h
        1_Domain_Code/xorlw.h
        1_Domain_Code/xorwf.h
        2_Application_Code/decode.h
        2_Application_Code/handler.h
        2_Application_Code/picSim.h
        2_Application_Code/readFileInterface.h
        2_Application_Code/utility.h
        3_Plugins/LSTFileHandler.h
        0_Abstraction_Code/customStack.cpp
        0_Abstraction_Code/picData.cpp
        0_Abstraction_Code/ram.cpp
        1_Domain_Code/addlw.cpp
        1_Domain_Code/addwf.cpp
        1_Domain_Code/andlw.cpp
        1_Domain_Code/andwf.cpp
        1_Domain_Code/bcf.cpp
        1_Domain_Code/bsf.cpp
        1_Domain_Code/btfsc.cpp
        1_Domain_Code/btfss.cpp
        1_Domain_Code/clrf.cpp
        1_Domain_Code/clrw.cpp
        1_Domain_Code/cmdcall.cpp
        1_Domain_Code/cmdgo.cpp
        1_Domain_Code/cmdreturn.cpp
        1_Domain_Code/comf.cpp
        1_Domain_Code/command.cpp
        1_Domain_Code/decf.cpp
        1_Domain_Code/decfsz.cpp
        1_Domain_Code/incf.cpp
        1_Domain_Code/incfsz.cpp
        1_Domain_Code/iorlw.cpp
        1_Domain_Code/iorwf.cpp
        1_Domain_Code/movf.cpp
        1_Domain_Code/movlw.cpp
        1_Domain_Code/movwf.cpp
        1_Domain_Code/nop.cpp
        1_Domain_Code/retfie.cpp
        1_Domain_Code/retlw.cpp
        1_Domain_Code/rlf.cpp
        1_Domain_Code/rrf.cpp
        1_Domain_Code/sublw.cpp
        1_Domain_Code/subwf.cpp
        1_Domain_Code/swapf.cpp
        1_Domain_Code/xorlw.cpp
        1_Domain_Code/xorwf.cpp
        2_Application_Code/decode.cpp
        2_Application_Code/handler.cpp
        2_Application_Code/picSim.cpp
        2_Application_Code/utility.cpp
        3_Plugins/LSTFileHandler.cpp
        )

add_library(${PROJECT_NAME} STATIC ${PicSim_lib})


