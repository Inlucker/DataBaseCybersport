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

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    for (auto &btn : buttons)
    {
        btn->setMinimumWidth(181);
        btn->setMinimumHeight(41);
    }
}

MatchEditDialog::~MatchEditDialog()
{
    delete ui;
}

void MatchEditDialog::setup(int m_id)
{
    match_bl = matches_repository->getMatch(m_id);

    int tournament_id =  match_bl->getTournamentId();
    updateTeamsList(tournament_id);

    team1_id = match_bl->getTeam1Id();
    setupTeams1Label();
    team2_id = match_bl->getTeam2Id();
    setupTeams2Label();

    winner_id = match_bl->getWinnerId();
    updateWinnerComboBox(winner_id);
    QString match_date = QString::fromStdString(match_bl->getDate());
    QStringList str_list = match_date.split("-");
    my_date = QDate(str_list[0].toInt(), str_list[1].toInt(), str_list[2].toInt());
    ui->dateEdit->setDate(my_date);
}

void MatchEditDialog::accept()
{
    if (team1_id && team2_id && my_date.isValid())
    {
        string date = "";
        date += to_string(my_date.year()) + "-";
        date += to_string(my_date.month()) + "-";
        date += to_string(my_date.day());

        match_bl->getTeam1Id() = team1_id;
        match_bl->getTeam2Id() = team2_id;
        match_bl->getWinnerId() = winner_id;
        match_bl->getDate() = date;
        matches_repository->updateMatch(*match_bl, match_bl->getId());
        QDialog::accept();
    }
    else
    {
        // Если некорректные данные
        QMessageBox::information(this, "Error", "Выберите все параметры");
        return;
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
    QString search = QString::number(team1_id);
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
    QString search = QString::number(team2_id);
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

void MatchEditDialog::updateWinnerComboBox(int w_id)
{
    ui->winner_comboBox->clear();
    ui->winner_comboBox->addItem("NULL");
    ui->winner_comboBox->addItem(ui->team1_label->text());
    ui->winner_comboBox->addItem(ui->team2_label->text());

    winner_id = w_id;

    if (winner_id == team1_id)
        ui->winner_comboBox->setCurrentIndex(1);
    else if (winner_id == team2_id)
        ui->winner_comboBox->setCurrentIndex(2);
}


void MatchEditDialog::on_choose_team1_btn_clicked()
{
    if (ui->teams_tableView->model())
    {
        QModelIndexList selectedRows = ui->teams_tableView->selectionModel()->selectedRows();
        if (selectedRows.size() != 1)
        {
            QMessageBox::information(this, "Error", "Выберите только одну команду");
            return;
        }
        team1_id = ui->teams_tableView->model()->data(selectedRows[0]).toInt();

        if (team1_id == team2_id)
        {
            team1_id = 0;
            QMessageBox::information(this, "Error", "Эта команда уже выбрана, выберите другую команду");
            return;
        }

        QModelIndex name_index = teams_table_model->index(selectedRows[0].row(), 4);
        ui->team1_label->setText(ui->teams_tableView->model()->data(name_index).toString());
        updateWinnerComboBox(0);
    }
}


void MatchEditDialog::on_choose_team2_btn_clicked()
{
    if (ui->teams_tableView->model())
    {
        QModelIndexList selectedRows = ui->teams_tableView->selectionModel()->selectedRows();
        if (selectedRows.size() != 1)
        {
            QMessageBox::information(this, "Error", "Выберите только одну команду");
            return;
        }
        team2_id = ui->teams_tableView->model()->data(selectedRows[0]).toInt();

        if (team1_id == team2_id)
        {
            team2_id = 0;
            QMessageBox::information(this, "Error", "Эта команда уже выбрана, выберите другую команду");
            return;
        }

        QModelIndex name_index = teams_table_model->index(selectedRows[0].row(), 4);
        ui->team2_label->setText(ui->teams_tableView->model()->data(name_index).toString());
        updateWinnerComboBox(0);
    }
}


void MatchEditDialog::on_winner_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
        winner_id = 0;
    else if (index == 1)
        winner_id = team1_id;
    else if (index == 2)
        winner_id = team2_id;
}

void MatchEditDialog::on_dateEdit_dateChanged(const QDate &date)
{
    my_date = date;
}

