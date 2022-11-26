QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/F_Principale.cpp \
    src/Arduino.cpp \
    src/f_selectionnerlescapteurs.cpp \
    src/f_visualiserlesvaleurs.cpp \
    src/listboxcapteur.cpp \
    src/listboxport.cpp\
    main.cpp

INCLUDEPATH += include
HEADERS += \
    include/Arduino.h \
    include/Listboxport.h \
    include/StructCapteur.h \
    include/f_selectionnerlescapteurs.h \
    include/f_visualiserlesvaleurs.h \
    include/F_Principale.h \
    include/listboxcapteur.h

FORMS += \
    ihm\f_selectionnerlescapteurs.ui \
    ihm\f_visualiserlesvaleurs.ui \
    ihm\F_Principale.ui


TRANSLATIONS += \
    GrovExAO_en.ts

CONFIG += lrelease

CONFIG += embed_translations

INCLUDEPATH += include\muParserX

#Chemin bibliothèque parser Lycée
LIBS += -LC:/Users/localw/Documents/Projet2022/realisations/GrovExAO/lib
LIBS += -lParserMathematique

#Chemin bibliothèque parser Maison
#LIBS += -LC:/Users/Vadco/Documents/Projet2022/realisations/GrovExAO/lib
#LIBS += -lParserMathematique

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
