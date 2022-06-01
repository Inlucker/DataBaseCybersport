#ifndef TOURNAMENTWINDOW_H
#define TOURNAMENTWINDOW_H

#include <QWidget>

#include "Controllers/TournamentController.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/TournamentsRepository.h"
#include "Repositorys/MatchesRepository.h"
#include "Repositorys/TeamsRepository.h"
#include "TableModels/TournamentsTableModel.h"
#include "TableModels/MatchesTableModel.h"
#include "TableModels/TeamsTableModel.h"

namespace Ui {
class TournamentWindow;
}

class TournamentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TournamentWindow(QWidget *parent = nullptr);
    ~TournamentWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "tournament_organizer");

signals:
    void exit();

private slots:
    void on_exit_btn_clicked();

    void on_get_mathces_btn_clicked();

    void on_tournaments_tableView_clicked(const QModelIndex &index);

    void on_matches_tableView_clicked(const QModelIndex &index);

    void on_teams_tableView_clicked(const QModelIndex &index);

private:
    void updateTournamentsList();
    void updateMatchesTeamsLists();

private:
    Ui::TournamentWindow *ui;

    unique_ptr<TournamentController> tournament_controller;

    shared_ptr<UsersRepository> users_repository;
    shared_ptr<TournamentsRepository> tournaments_repository;
    shared_ptr<MatchesRepository> matches_repository;
    shared_ptr<TeamsRepository> teams_repository;

    shared_ptr<TournamentsTableModel> tournaments_table_model;
    shared_ptr<MatchesTableModel> matches_table_model;
    shared_ptr<TeamsTableModel> teams_table_model;
};

#endif // TOURNAMENTWINDOW_H
