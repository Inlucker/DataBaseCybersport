#ifndef TOURNAMENTCREATIONDIALOG_H
#define TOURNAMENTCREATIONDIALOG_H

#include <QDialog>

#include "Repositorys/TournamentsRepository.h"
#include "Repositorys/TeamsRepository.h"
#include "Repositorys/CountriesRepository.h"
#include "TableModels/TeamsTableModel.h"

namespace Ui {
class TournamentCreationDialog;
}

class TournamentCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentCreationDialog(QWidget *parent = nullptr);
    ~TournamentCreationDialog();

    void setup(int org_id);

protected:
    virtual void accept() override;

private slots:
    void on_pushButton_clicked();

    void on_teams_tableView_clicked(const QModelIndex &index);

    void on_delete_team_btn_clicked();

    void on_my_teams_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

private:
    void updateTeamsList();
    void updateMyTeamsList();
    void updateCountriesList();

private:
    Ui::TournamentCreationDialog *ui;

    int tournament_id = 0;
    int country_id = 0;
    int organizer_id = 0;
    //string tournament_name = "";
    //int prizepool = 0;
    //vector<int> teams;

    shared_ptr<TournamentsRepository> tournaments_repository;
    shared_ptr<TeamsRepository> teams_repository;
    shared_ptr<CountriesRepository> countries_repository;

    shared_ptr<TeamsTableModel> teams_table_model;
    shared_ptr<TeamsTableModel> my_teams_table_model;
};

#endif // TOURNAMENTCREATIONDIALOG_H
