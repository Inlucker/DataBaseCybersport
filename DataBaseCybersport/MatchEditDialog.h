#ifndef MATCHEDITDIALOG_H
#define MATCHEDITDIALOG_H

#include <QDialog>
#include <QDate>

#include "EssensitiesBL/MatchBL.h"
#include "Repositorys/MatchesRepository.h"
#include "Repositorys/TeamsRepository.h"
#include "TableModels/TeamsTableModel.h"


namespace Ui {
class MatchEditDialog;
}

class MatchEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatchEditDialog(QWidget *parent = nullptr);
    ~MatchEditDialog();

    void setup(int match_id);

protected:
    virtual void accept() override;

private slots:
    void on_teams_tableView_clicked(const QModelIndex &index);

    void on_choose_team1_btn_clicked();

    void on_choose_team2_btn_clicked();

    void on_winner_comboBox_currentIndexChanged(int index);

    void on_dateEdit_dateChanged(const QDate &date);

private:
    void updateTeamsList(int tournament_id);
    void setupTeams1Label();
    void setupTeams2Label();
    void updateWinnerComboBox(int w_id);

private:
    Ui::MatchEditDialog *ui;

    //int tournament_id = 0;
    shared_ptr<MatchBL> match_bl;
    int team1_id = 0;
    int team2_id = 0;
    int winner_id = 0;
    QDate my_date;

    shared_ptr<TeamsTableModel> teams_table_model;

    shared_ptr<TeamsRepository> teams_repository;
    shared_ptr<MatchesRepository> matches_repository;
};

#endif // MATCHEDITDIALOG_H
