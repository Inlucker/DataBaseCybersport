#ifndef MATCHCREATIONDIALOG_H
#define MATCHCREATIONDIALOG_H

#include <QDialog>
#include <QDate>
#include <QDateEdit>

#include "TableModels/TeamsTableModel.h"
#include "TableModels/StudiosTableModel.h"
#include "TableModels/CommentatorsTableModel.h"

#include "Repositorys/TournamentsRepository.h"
#include "Repositorys/TeamsRepository.h"
#include "Repositorys/StudioRepository.h"
#include "Repositorys/CommentatorRepository.h"
#include "Repositorys/MatchesRepository.h"

namespace Ui {
class MatchCreationDialog;
}

class MatchCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatchCreationDialog(QWidget *parent = nullptr);
    ~MatchCreationDialog();

    void setup(int org_id);

protected:
    virtual void accept() override;

private slots:
    void on_tournament_comboBox_currentIndexChanged(int index);

    void on_teams_tableView_clicked(const QModelIndex &index);

    void on_studios_tableView_clicked(const QModelIndex &index);

    void on_commentatros_tableView_clicked(const QModelIndex &index);

    void on_choose_team1_btn_clicked();

    void on_choose_team2_btn_clicked();

    void on_choose_studio_btn_clicked();

    void on_choose_commentator_btn_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void updateTeamsList(int tournament_id);
    void updateStudiosList();
    void updateCommentatorsList();

private:
    Ui::MatchCreationDialog *ui;

    shared_ptr<TeamsTableModel> teams_table_model;
    shared_ptr<StudiosTableModel> studios_table_model;
    shared_ptr<CommentatorsTableModel> commentators_table_model;

    shared_ptr<TournamentsRepository> tournaments_repository;
    shared_ptr<TeamsRepository> teams_repository;
    shared_ptr<StudioRepository> studio_repository;
    shared_ptr<CommentatorRepository> commentator_repository;
    shared_ptr<MatchesRepository> matches_repository;

    vector<int> tournaments_id;
    int previous_tournament_index = -1;
    int tournament_id = 0;
    int team1_id = 0;
    int team2_id = 0;
    int studio_id = 0;
    int commentator_id = 0;
    QDate my_date;
};

#endif // MATCHCREATIONDIALOG_H
