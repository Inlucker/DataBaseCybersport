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

    players_repository = make_shared<PlayersRepository>();
    teams_repository = make_shared<TeamsRepository>();
    countries_repository = make_shared<CountriesRepository>();


    free_players_table_model = make_shared<PlayersTableModel>();
    my_players_table_model = make_shared<PlayersTableModel>();
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
    qDebug() << r.toString();
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
    //ui->free_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->free_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->free_tableView->setModel(free_players_table_model.get());
    qDebug() << free_players_table_model->columnCount();
    for (int i = 0; i < free_players_table_model->columnCount(); i++)
       ui->free_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

}

void TeamWindow::updateMyPlayerList()
{
    shared_ptr<vector<PlayerDTO>> my_players_dto = players_repository->getPlayersDTOByTeam(team_controller->getUser()->getId());
    my_players_table_model = make_shared<PlayersTableModel>(my_players_dto);
    ui->my_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->my_tableView->setModel(my_players_table_model.get());
    for (int i = 0; i < my_players_table_model->columnCount(); i++)
        ui->my_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void TeamWindow::updateLists()
{
    updateFreePlayersList();
    updateMyPlayerList();
}


void TeamWindow::on_add_btn_clicked()
{
    try
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
            player_bl->getTeamId() = 3;
            //PlayerBL new_player_bl(*player_bl);
            //PlayerBL new_player_bl(player_bl->getId(), 3, player_bl->getCountryId(), player_bl->get());
            players_repository->updatePlayer(*player_bl, id);
        }
        updateLists();
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

