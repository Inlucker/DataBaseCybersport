#include "TeamWindow.h"
#include "ui_TeamWindow.h"

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
    updateFreePlayersList();
    updateMyPlayerList();
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
}

void TeamWindow::updateMyPlayerList()
{
    shared_ptr<vector<PlayerDTO>> my_players_dto = players_repository->getPlayersDTOByTeam(team_controller->getUser()->getId());
    my_players_table_model = make_shared<PlayersTableModel>(my_players_dto);
    ui->my_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->my_tableView->setModel(my_players_table_model.get());
}


void TeamWindow::on_add_btn_clicked()
{

}

