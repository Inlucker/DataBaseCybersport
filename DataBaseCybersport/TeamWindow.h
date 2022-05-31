#ifndef TEAMWINDOW_H
#define TEAMWINDOW_H

#include <QWidget>
#include <string>
#include <memory>

using namespace std;

#include "Essensities/UserBL.h"
#include "Controllers/TeamController.h"

namespace Ui {
class TeamWindow;
}

class TeamWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeamWindow(QWidget *parent = nullptr);
    ~TeamWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "Team_Captain");

private slots:
    void on_exit_btn_clicked();

signals:
    void exit();

private:
    void updateFreePlayersList();
    void updateMyPlayerList();
    void updateLists();

private:
    Ui::TeamWindow *ui;

    unique_ptr<TeamController> team_controller;

    //shared_ptr<PlayersRepository> players_repository;
};

#endif // TEAMWINDOW_H
