#include "TournamentCreationDialog.h"
#include "ui_TournamentCreationDialog.h"

#include <QMessageBox>

#include "Errors/BaseError.h"

TournamentCreationDialog::TournamentCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentCreationDialog)
{
    ui->setupUi(this);

    tournaments_repository = make_shared<TournamentsRepository>();
    teams_repository = make_shared<TeamsRepository>();
    countries_repository = make_shared<CountriesRepository>();

    teams_table_model = make_shared<TeamsTableModel>();
    my_teams_table_model = make_shared<TeamsTableModel>();
    ui->my_teams_tableView->setModel(my_teams_table_model.get());

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    for (auto &btn : buttons)
    {
        btn->setMinimumWidth(181);
        btn->setMinimumHeight(41);
    }
}

TournamentCreationDialog::~TournamentCreationDialog()
{
    delete ui;
}

void TournamentCreationDialog::setup(int org_id)
{
    organizer_id = org_id;
    updateTeamsList();
    updateMyTeamsList();
    updateCountriesList();
}

void TournamentCreationDialog::accept()
{
    string tournament_name = ui->lineEdit->text().toStdString();
    int prizepool = ui->spinBox->value();
    if (tournament_name.size() > 0 && prizepool > 0 && country_id)
    {
        TournamentBL tournament_bl(0, country_id, organizer_id, tournament_name, prizepool);
        tournaments_repository->addTournament(tournament_bl);
        QDialog::accept();
    }
    else
    {
        // Если некорректные данные
        QMessageBox::information(this, "Error", "Выберите все параметры");
        return;
    }
}

void TournamentCreationDialog::updateTeamsList()
{
    shared_ptr<vector<TeamDTO>> teams_dto = teams_repository->getAllTeams();
    teams_table_model = make_shared<TeamsTableModel>(teams_dto);

    ui->teams_tableView->setModel(teams_table_model.get());
    for (int i = 0; i < teams_table_model->columnCount(); i++)
        ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void TournamentCreationDialog::updateMyTeamsList()
{
    my_teams_table_model = make_shared<TeamsTableModel>();
    ui->my_teams_tableView->setModel(my_teams_table_model.get());
}

void TournamentCreationDialog::updateCountriesList()
{
    shared_ptr<vector<string>> countries = countries_repository->getAllCountries();
    ui->comboBox->clear();
    for (auto &country : *countries)
    {
        ui->comboBox->addItem(QString::fromStdString(country));
    }
}


void TournamentCreationDialog::on_pushButton_clicked()
{
    try
    {
        if (ui->teams_tableView->model())
        {
            QModelIndexList selectedRows = ui->teams_tableView->selectionModel()->selectedRows();
            if (selectedRows.size() < 1)
            {
                QMessageBox::information(this, "Error", "Выберите только хотябы одну команду");
                return;
            }
            int delta = 0;
            for (auto &ind : selectedRows)
            {
                TeamDTO team = teams_table_model->deleteRow(ind.row() - (delta++));
                my_teams_table_model->addTeam(team);
            }

            for (int i = 0; i < teams_table_model->columnCount(); i++)
            {
                ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
                ui->my_teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
            }
        }
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void TournamentCreationDialog::on_teams_tableView_clicked(const QModelIndex &index)
{
    ui->teams_tableView->selectRow(index.row());
}


void TournamentCreationDialog::on_delete_team_btn_clicked()
{
    try
    {
        if (ui->my_teams_tableView->model())
        {
            QModelIndexList selectedRows = ui->my_teams_tableView->selectionModel()->selectedRows();
            if (selectedRows.size() < 1)
            {
                QMessageBox::information(this, "Error", "Выберите только хотябы одну команду");
                return;
            }
            int delta = 0;
            for (auto &ind : selectedRows)
            {
                TeamDTO team = my_teams_table_model->deleteRow(ind.row() - (delta++));
                teams_table_model->addTeam(team);
            }

            for (int i = 0; i < teams_table_model->columnCount(); i++)
            {
                ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
                ui->my_teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
            }
        }
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void TournamentCreationDialog::on_my_teams_tableView_clicked(const QModelIndex &index)
{
    ui->my_teams_tableView->selectRow(index.row());
}


void TournamentCreationDialog::on_comboBox_currentIndexChanged(int index)
{
    country_id = index + 1;
}

