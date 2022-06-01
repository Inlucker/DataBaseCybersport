QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/BaseController.cpp \
    Controllers/StudioController.cpp \
    Controllers/TeamController.cpp \
    Controllers/TournamentController.cpp \
    EssensitiesBL/CommentatorBL.cpp \
    EssensitiesBL/PlayerBL.cpp \
    EssensitiesDTO/CommentatorDTO.cpp \
    EssensitiesDTO/PlayerDTO.cpp \
    EssensitiesBL/TeamBL.cpp \
    EssensitiesDTO/StudioDTO.cpp \
    EssensitiesDTO/TeamDTO.cpp \
    EssensitiesBL/UserBL.cpp \
    EssensitiesDTO/TournamentDTO.cpp \
    Logger.cpp \
    Repositorys/CommentatorRepository.cpp \
    Repositorys/CountriesRepository.cpp \
    Repositorys/ICommentatorsRepository.cpp \
    Repositorys/ICountriesRepository.cpp \
    Repositorys/ITeamsRepository.cpp \
    Repositorys/StudioRepository.cpp \
    Repositorys/TeamsRepository.cpp \
    Repositorys/TournamentsRepository.cpp \
    StudioWindow.cpp \
    TableModels/CommentatorsTableModel.cpp \
    TableModels/PlayersTableModel.cpp \
    Repositorys/IPlayersRepository.cpp \
    Repositorys/IUserRolesRepository.cpp \
    Repositorys/IUsersRepository.cpp \
    Repositorys/PlayersRepository.cpp \
    Repositorys/UserRolesRepository.cpp \
    Repositorys/UsersRepository.cpp \
    Settings.cpp \
    TableModels/StudiosTableModel.cpp \
    TableModels/TeamsTableModel.cpp \
    TableModels/TournamentsTableModel.cpp \
    TeamWindow.cpp \
    TournamentWindow.cpp \
    main.cpp \
    BaseWindow.cpp

HEADERS += \
    BaseWindow.h \
    Controllers/BaseController.h \
    Controllers/StudioController.h \
    Controllers/TeamController.h \
    Controllers/TournamentController.h \
    Errors/BaseError.h \
    Errors/RepositoryErrors.h \
    EssensitiesBL/CommentatorBL.h \
    EssensitiesBL/PlayerBL.h \
    EssensitiesDTO/CommentatorDTO.h \
    EssensitiesDTO/PlayerDTO.h \
    EssensitiesBL/TeamBL.h \
    EssensitiesDTO/StudioDTO.h \
    EssensitiesDTO/TeamDTO.h \
    EssensitiesBL/UserBL.h \
    EssensitiesDTO/TournamentDTO.h \
    Logger.h \
    Repositorys/CommentatorRepository.h \
    Repositorys/CountriesRepository.h \
    Repositorys/ICommentatorsRepository.h \
    Repositorys/ICountriesRepository.h \
    Repositorys/ITeamsRepository.h \
    Repositorys/StudioRepository.h \
    Repositorys/TeamsRepository.h \
    Repositorys/TournamentsRepository.h \
    StudioWindow.h \
    TableModels/CommentatorsTableModel.h \
    TableModels/PlayersTableModel.h \
    Repositorys/IPlayersRepository.h \
    Repositorys/IUserRolesRepository.h \
    Repositorys/IUsersRepository.h \
    Repositorys/PlayersRepository.h \
    Repositorys/UserRolesRepository.h \
    Repositorys/UsersRepository.h \
    Settings.h \
    TableModels/StudiosTableModel.h \
    TableModels/TeamsTableModel.h \
    TableModels/TournamentsTableModel.h \
    TeamWindow.h \
    TournamentWindow.h

FORMS += \
    BaseWindow.ui \
    StudioWindow.ui \
    TeamWindow.ui \
    TournamentWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq
else:unix: LIBS += -L'C:/Program Files/PostgreSQL/13/lib/' -lpq

INCLUDEPATH += 'C:/Program Files/PostgreSQL/13/include'
DEPENDPATH += 'C:/Program Files/PostgreSQL/13/include'
