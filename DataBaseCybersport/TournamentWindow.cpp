#include "TournamentWindow.h"
#include "ui_TournamentWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
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
    matches_repository = make_shared<MatchesRepository>();

    tournaments_table_model = make_shared<TournamentsTableModel>();
    matches_table_model = make_shared<MatchesTableModel>();
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

void TournamentWindow::updateMatchesList()
{
    QModelIndexList selectedRows = ui->tournaments_tableView->selectionModel()->selectedRows();
    if (selectedRows.size() != 1)
    {
        QMessageBox::information(this, "Error", "Выберите только один турнир");
        return;
    }
    int tournament_id = ui->tournaments_tableView->model()->data(selectedRows[0]).toInt();

    shared_ptr<vector<MatchDTO>> matches_dto = matches_repository->getMatchesDTOByTournament(tournament_id);
    matches_table_model = make_shared<MatchesTableModel>(matches_dto);

    ui->matches_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->matches_tableView->setModel(matches_table_model.get());
    for (int i = 0; i < matches_table_model->columnCount(); i++)
        ui->matches_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}


void TournamentWindow::on_get_mathces_btn_clicked()
{
    try
    {
        updateMatchesList();
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


void TournamentWindow::on_tournaments_tableView_clicked(const QModelIndex &index)
{
    ui->tournaments_tableView->selectRow(index.row());
}


void TournamentWindow::on_matches_tableView_clicked(const QModelIndex &index)
{
    ui->matches_tableView->selectRow(index.row());
}

