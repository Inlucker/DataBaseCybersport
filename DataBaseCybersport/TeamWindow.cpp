#include "TeamWindow.h"
#include "ui_TeamWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
#include "Logger.h"
#include "Settings.h"

TeamWindow::TeamWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamWindow)
{
    ui->setupUi(this);

    team_controller = make_unique<TeamController>();

    users_repository = make_shared<UsersRepository>();
    players_repository = make_shared<PlayersRepository>();
    teams_repository = make_shared<TeamsRepository>();
    countries_repository = make_shared<CountriesRepository>();

    free_players_table_model = make_shared<PlayersTableModel>();
    my_players_table_model = make_shared<PlayersTableModel>();
    teams_table_model = make_shared<TeamsTableModel>();

    //ui->delete_user_btn->hide();
}

TeamWindow::~TeamWindow()
{
    delete ui;
}

void TeamWindow::login(shared_ptr<UserBL> user_bl, string role)
{
    team_controller->login(user_bl);
    //users_repository->setRole(user_bl->getRole(), user_bl->getRole());
    QVariant r(QString::fromStdString(role));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    //updateFreePlayersList();
    //updateMyPlayerList();
    updateLists();
}

void TeamWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button";
    this->hide();
    team_controller->logout();
    emit exit();
}

void TeamWindow::updateFreePlayersList()
{
    shared_ptr<vector<PlayerDTO>> my_players_dto = players_repository->getFreePlayersDTO();

    free_players_table_model = make_shared<PlayersTableModel>(my_players_dto);
    ui->free_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->free_tableView->setModel(free_players_table_model.get());
    for (int i = 0; i < free_players_table_model->columnCount(); i++)
       ui->free_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void TeamWindow::updateMyPlayerList()
{
    /*shared_ptr<vector<TeamDTO>> teams_dto = teams_repository->getTeamsByCaptainId(team_controller->getUser()->getId());
    shared_ptr<vector<PlayerDTO>> all_my_players_dto = make_shared<vector<PlayerDTO>>();
    for (auto& team : *teams_dto)
    {
        shared_ptr<vector<PlayerDTO>> tmp_my_players_dto = players_repository->getPlayersDTOByTeam(team.getId());
        all_my_players_dto->insert(all_my_players_dto->end(), tmp_my_players_dto->begin(), tmp_my_players_dto->end());
    }*/
    shared_ptr<vector<PlayerDTO>> all_my_players_dto = players_repository->getPlayersDTOByCaptain(team_controller->getUser()->getId());

    my_players_table_model = make_shared<PlayersTableModel>(all_my_players_dto);
    ui->my_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->my_tableView->setModel(my_players_table_model.get());
    for (int i = 0; i < my_players_table_model->columnCount(); i++)
        ui->my_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void TeamWindow::updateTeamsList()
{
    shared_ptr<vector<TeamDTO>> teams_dto = teams_repository->getTeamsByCaptainId(team_controller->getUser()->getId());

    ui->my_teams_comboBox->clear();
    for (auto& team : *teams_dto)
    {
        ui->my_teams_comboBox->addItem(QString::fromStdString(team.getName()));
    }

    teams_table_model = make_shared<TeamsTableModel>(teams_dto);
    ui->teams_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->teams_tableView->setModel(teams_table_model.get());
    for (int i = 0; i < teams_table_model->columnCount(); i++)
        ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void TeamWindow::updateLists()
{
    updateFreePlayersList();
    updateMyPlayerList();
    updateTeamsList();
}

void TeamWindow::on_add_btn_clicked()
{
    try
    {
        if (ui->free_tableView->model())
        {
            QModelIndexList selectedRows = ui->free_tableView->selectionModel()->selectedRows();
            if (selectedRows.size() <= 0)
            {
                QMessageBox::information(this, "Error", "Выберите хотябы одного игрока из списка свободных");
                return;
            }
            for(auto& ind : selectedRows)
            {
                int id = ui->free_tableView->model()->data(ind).toInt();
                shared_ptr<PlayerBL> player_bl = players_repository->getPlayer(id);

                QString new_team = ui->my_teams_comboBox->currentText();
                QModelIndex founded_index;
                int row_count = teams_table_model->rowCount();
                for (int i = 0; i < row_count; i++)
                {
                    QModelIndex idx = teams_table_model->index(i, 4);
                    if (teams_table_model->data(idx).toString() == new_team)
                    {
                       founded_index = teams_table_model->index(i, 0);
                       break;
                    }
                }
                int new_team_id = teams_table_model->data(founded_index).toInt();

                player_bl->getTeamId() = new_team_id;
                players_repository->updatePlayer(*player_bl, id);
            }
            updateLists();
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


void TeamWindow::on_delete_btn_clicked()
{
    try
    {
        if (ui->my_tableView->model())
        {
            QModelIndexList selectedRows = ui->my_tableView->selectionModel()->selectedRows();
            if (selectedRows.size() <= 0)
            {
                QMessageBox::information(this, "Error", "Выберите хотябы одного вашего игрока из списка");
                return;
            }
            for(auto& ind : selectedRows)
            {
                int id = ui->my_tableView->model()->data(ind).toInt();
                shared_ptr<PlayerBL> player_bl = players_repository->getPlayer(id);

                player_bl->getTeamId() = 0;
                players_repository->updatePlayer(*player_bl, id);
            }
            updateLists();
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


void TeamWindow::on_free_tableView_clicked(const QModelIndex &index)
{
    ui->free_tableView->selectRow(index.row());
}


void TeamWindow::on_my_tableView_clicked(const QModelIndex &index)
{
    ui->my_tableView->selectRow(index.row());
}


void TeamWindow::on_teams_tableView_clicked(const QModelIndex &index)
{
    ui->teams_tableView->selectRow(index.row());
}


void TeamWindow::on_delete_user_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed DELETE THIS USER button";
        users_repository->deleteUser(team_controller->getUser()->getId());
        this->hide();
        team_controller->logout();
        emit exit();
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

