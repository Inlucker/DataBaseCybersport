#ifndef TOURNAMENTWINDOW_H
#define TOURNAMENTWINDOW_H

#include <QWidget>

#include "Controllers/TournamentController.h"
#include "Repositorys/UsersRepository.h"

namespace Ui {
class TournamentWindow;
}

class TournamentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TournamentWindow(QWidget *parent = nullptr);
    ~TournamentWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "tournament_organizer");

signals:
    void exit();

private slots:
    void on_exit_btn_clicked();

private:
    Ui::TournamentWindow *ui;

    unique_ptr<TournamentController> tournament_controller;

    shared_ptr<UsersRepository> users_repository;
};

#endif // TOURNAMENTWINDOW_H
