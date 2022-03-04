project(PicSim_lib)

set(PicSim_lib
        customStack.h
        picData.h
        ram.h
        addlw.h
        addwf.h
        andlw.h
        andwf.h
        bcf.h
        bsf.h
        btfsc.h
        btfss.h
        clrf.h
        clrw.h
        cmdcall.h
        cmdgo.h
        cmdreturn.h
        comf.h
        command.h
        decf.h
        decfsz.h
        incf.h
        incfsz.h
        iorlw.h
        iorwf.h
        movf.h
        movlw.h
        movwf.h
        nop.h
        retfie.h
        retlw.h
        rlf.h
        rrf.h
        sublw.h
        subwf.h
        swapf.h
        xorlw.h
        xorwf.h
        decode.h
        handler.h
        picSim.h
        readFileInterface.h
        utility.h
        #info.h
        #infodialog.h
        LSTFileHandler.h
        #picsimgui.h
        customStack.cpp
        picData.cpp
        ram.cpp
        addlw.cpp
        addwf.cpp
        andlw.cpp
        andwf.cpp
        bcf.cpp
        bsf.cpp
        btfsc.cpp
        btfss.cpp
        clrf.cpp
        clrw.cpp
        cmdcall.cpp
        cmdgo.cpp
        cmdreturn.cpp
        comf.cpp
        command.cpp
        decf.cpp
        decfsz.cpp
        incf.cpp
        incfsz.cpp
        iorlw.cpp
        iorwf.cpp
        movf.cpp
        movlw.cpp
        movwf.cpp
        nop.cpp
        retfie.cpp
        retlw.cpp
        rlf.cpp
        rrf.cpp
        sublw.cpp
        subwf.cpp
        swapf.cpp
        xorlw.cpp
        xorwf.cpp
        decode.cpp
        handler.cpp
        picSim.cpp
        utility.cpp
        #info.cpp
        #infodialog.cpp
        LSTFileHandler.cpp
        #picsimgui.cpp
        )

add_library(${PROJECT_NAME} STATIC ${PicSim_lib})

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64")
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets PicSim_lib)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
