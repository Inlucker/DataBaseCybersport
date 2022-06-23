#ifndef STUDIOWINDOW_H
#define STUDIOWINDOW_H

#include <QWidget>

#include "Controllers/StudioController.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/CommentatorRepository.h"
#include "Repositorys/StudioRepository.h"
#include "Repositorys/CountriesRepository.h"
#include "TableModels/CommentatorsTableModel.h"
#include "TableModels/StudiosTableModel.h"

namespace Ui {
class StudioWindow;
}

class StudioWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudioWindow(QWidget *parent = nullptr);
    ~StudioWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "studio_owner");

signals:
    void exit();

private slots:
    void on_exit_btn_clicked();

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_free_tableView_clicked(const QModelIndex &index);

    void on_my_tableView_clicked(const QModelIndex &index);

    void on_studios_tableView_clicked(const QModelIndex &index);

    void on_delete_user_btn_clicked();

    void on_create_studio_btn_clicked();

private:
    void updateFreeCommentatorsList();
    void updateMyCommentatorsList();
    void updateStudiosList();
    void updateCountries();
    void updateLists();

private:
    Ui::StudioWindow *ui;

    unique_ptr<StudioController> studio_controller;

    shared_ptr<UsersRepository> users_repository;
    shared_ptr<CommentatorRepository> commentator_repository;
    shared_ptr<StudioRepository> studio_repository;
    shared_ptr<CountriesRepository> countries_repository;

    shared_ptr<CommentatorsTableModel> free_coms_table_model;
    shared_ptr<CommentatorsTableModel> my_coms_table_model;
    shared_ptr<StudiosTableModel> studios_table_model;
};

#endif // STUDIOWINDOW_H
