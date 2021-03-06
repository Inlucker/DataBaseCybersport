#ifndef TEAMWINDOW_H
#define TEAMWINDOW_H

#include <QWidget>
#include <string>
#include <memory>

using namespace std;

#include "EssensitiesBL/UserBL.h"
#include "EssensitiesDTO/PlayerDTO.h"

#include "Controllers/TeamController.h"

#include "Repositorys/UsersRepository.h"
#include "Repositorys/PlayersRepository.h"
#include "Repositorys/TeamsRepository.h"
#include "Repositorys/CountriesRepository.h"
#include "Repositorys/SponsorsRepository.h"

#include "TableModels/PlayersTableModel.h"
#include "TableModels/TeamsTableModel.h"

namespace Ui {
class TeamWindow;
}

class TeamWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeamWindow(QWidget *parent = nullptr);
    ~TeamWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "team_captain");

private slots:
    void on_exit_btn_clicked();

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_free_tableView_clicked(const QModelIndex &index);

    void on_my_tableView_clicked(const QModelIndex &index);

    void on_teams_tableView_clicked(const QModelIndex &index);

    void on_delete_user_btn_clicked();

    void on_create_team_btn_clicked();

signals:
    void exit();

private:
    void updateFreePlayersList();
    void updateMyPlayerList();
    void updateTeamsList();
    void updateCountries();
    void updateSponsors();
    void updateLists();

private:
    Ui::TeamWindow *ui;

    unique_ptr<TeamController> team_controller;

    shared_ptr<UsersRepository> users_repository;
    shared_ptr<PlayersRepository> players_repository;
    shared_ptr<TeamsRepository> teams_repository;
    shared_ptr<CountriesRepository> countries_repository;
    shared_ptr<SponsorsRepository> sponsors_repository;

    shared_ptr<PlayersTableModel> free_players_table_model;
    shared_ptr<PlayersTableModel> my_players_table_model;
    shared_ptr<TeamsTableModel> teams_table_model;
};

#endif // TEAMWINDOW_H
