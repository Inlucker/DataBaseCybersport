#include "MatchEditDialog.h"
#include "ui_MatchEditDialog.h"

#include <QMessageBox>

MatchEditDialog::MatchEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatchEditDialog)
{
    ui->setupUi(this);

    teams_table_model = make_shared<TeamsTableModel>();

    teams_repository = make_shared<TeamsRepository>();
    matches_repository = make_shared<MatchesRepository>();
}

MatchEditDialog::~MatchEditDialog()
{
    delete ui;
}

void MatchEditDialog::setup(int match_id)
{
    shared_ptr<MatchBL> match_bl = matches_repository->getMatch(match_id);

    int tournament_id =  match_bl->getTournamentId();
    updateTeamsList(tournament_id);

    team_id1 = match_bl->getTeam1Id();
    setupTeams1Label();
    team_id2 = match_bl->getTeam2Id();
    setupTeams2Label();

    winner_id = match_bl->getWinnerId();
    setupWinnerComboBox();
    string match_date = match_bl->getDate();
    //date =
}

void MatchEditDialog::accept()
{
    if (!(1))
    {
        // Если некорректные данные
        QMessageBox::information(this, "Error", "Выберите все параметры");
        return;
    }
    else
    {
        QDialog::accept();
    }
}

void MatchEditDialog::on_teams_tableView_clicked(const QModelIndex &index)
{
    ui->teams_tableView->selectRow(index.row());
}

void MatchEditDialog::updateTeamsList(int tournament_id)
{
    shared_ptr<vector<TeamDTO>> teams_dto = teams_repository->getTeamsByTournament(tournament_id);
    teams_table_model = make_shared<TeamsTableModel>(teams_dto);

    ui->teams_tableView->setModel(teams_table_model.get());
    for (int i = 0; i < teams_table_model->columnCount(); i++)
        ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void MatchEditDialog::setupTeams1Label()
{
    int row_count = teams_table_model->rowCount();
    QString search = QString::number(team_id1);
    QModelIndex founded_index;
    for(int i = 0; i < row_count; i++)
    {
        QModelIndex idx = teams_table_model->index(i, 0);
        if (teams_table_model->data(idx).toString() == search)
        {
           founded_index = teams_table_model->index(i, 4);
           break;
        }
    }
    ui->team1_label->setText(teams_table_model->data(founded_index).toString());
}

void MatchEditDialog::setupTeams2Label()
{
    int row_count = teams_table_model->rowCount();
    QString search = QString::number(team_id2);
    QModelIndex founded_index;
    for(int i = 0; i < row_count; i++)
    {
        QModelIndex idx = teams_table_model->index(i, 0);
        if (teams_table_model->data(idx).toString() == search)
        {
           founded_index = teams_table_model->index(i, 4);
           break;
        }
    }
    ui->team2_label->setText(teams_table_model->data(founded_index).toString());
}

void MatchEditDialog::setupWinnerComboBox()
{
    ui->winner_comboBox->clear();
    ui->winner_comboBox->addItem("NULL");
    ui->winner_comboBox->addItem(ui->team1_label->text());
    ui->winner_comboBox->addItem(ui->team2_label->text());

    if (winner_id == team_id1)
        ui->winner_comboBox->setCurrentIndex(1);
    else if (winner_id == team_id2)
        ui->winner_comboBox->setCurrentIndex(2);
}

