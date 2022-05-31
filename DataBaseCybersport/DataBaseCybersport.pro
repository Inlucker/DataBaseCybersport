QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/BaseController.cpp \
    Controllers/TeamController.cpp \
    Essensities/UserBL.cpp \
    Logger.cpp \
    Repositorys/IUserRolesRepository.cpp \
    Repositorys/IUsersRepository.cpp \
    Repositorys/UserRolesRepository.cpp \
    Repositorys/UsersRepository.cpp \
    Settings.cpp \
    TeamWindow.cpp \
    main.cpp \
    BaseWindow.cpp

HEADERS += \
    BaseWindow.h \
    Controllers/BaseController.h \
    Controllers/TeamController.h \
    Errors/BaseError.h \
    Errors/RepositoryErrors.h \
    Essensities/UserBL.h \
    Logger.h \
    Repositorys/IUserRolesRepository.h \
    Repositorys/IUsersRepository.h \
    Repositorys/UserRolesRepository.h \
    Repositorys/UsersRepository.h \
    Settings.h \
    TeamWindow.h

FORMS += \
    BaseWindow.ui \
    TeamWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'
