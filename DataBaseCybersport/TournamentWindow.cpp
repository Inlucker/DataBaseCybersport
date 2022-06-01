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
}

void TournamentWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button in TournamentWindow";
    this->hide();
    tournament_controller->logout();
    emit exit();
}

