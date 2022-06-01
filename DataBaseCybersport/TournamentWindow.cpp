#include "TournamentWindow.h"
#include "ui_TournamentWindow.h"

#include "Settings.h"
#include "Logger.h"

TournamentWindow::TournamentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TournamentWindow)
{
    ui->setupUi(this);

    tournament_controller = make_unique<TournamentController>();

    users_repository = make_shared<UsersRepository>();
    tournaments_repository = make_shared<TournamentsRepository>();

    tournaments_table_model = make_shared<TournamentsTableModel>();
}

TournamentWindow::~TournamentWindow()
{
    delete ui;
}

void TournamentWindow::login(shared_ptr<UserBL> user_bl, string role)
{
    tournament_controller->login(user_bl);
    QVariant r(QString::fromStdString(role));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    updateTournamentsList();
}

void TournamentWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button in TournamentWindow";
    this->hide();
    tournament_controller->logout();
    emit exit();
}

void TournamentWindow::updateTournamentsList()
{
    shared_ptr<vector<TournamentDTO>> tournaments_dto = tournaments_repository->getTournamentsDTOByOrgId(tournament_controller->getUser()->getId());
    tournaments_table_model = make_shared<TournamentsTableModel>(tournaments_dto);

    ui->tournaments_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tournaments_tableView->setModel(tournaments_table_model.get());
    for (int i = 0; i < tournaments_table_model->columnCount(); i++)
        ui->tournaments_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

