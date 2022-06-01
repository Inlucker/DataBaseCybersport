#include "StudioWindow.h"
#include "ui_StudioWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
#include "Logger.h"
#include "Settings.h"

StudioWindow::StudioWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudioWindow)
{
    ui->setupUi(this);

    studio_controller = make_unique<StudioController>();

    commentator_repository = make_shared<CommentatorRepository>();
    studio_repository = make_shared<StudioRepository>();

    free_coms_table_model = make_shared<CommentatorsTableModel>();
    my_coms_table_model = make_shared<CommentatorsTableModel>();
    studios_table_model = make_shared<StudiosTableModel>();

    ui->delete_user_btn->hide();
}

StudioWindow::~StudioWindow()
{
    delete ui;
}

void StudioWindow::login(shared_ptr<UserBL> user_bl, string role)
{
    studio_controller->login(user_bl);
    QVariant r(QString::fromStdString(role));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    updateLists();
}

void StudioWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button in StudioWindow";
    this->hide();
    studio_controller->logout();
    emit exit();
}

void StudioWindow::updateFreeCommentatorsList()
{
    shared_ptr<vector<CommentatorDTO>> coms_dto = commentator_repository->getCommentatorsDTOByStudioId(0);
    free_coms_table_model = make_shared<CommentatorsTableModel>(coms_dto);
    ui->free_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->free_tableView->setModel(free_coms_table_model.get());
    for (int i = 0; i < free_coms_table_model->columnCount(); i++)
        ui->free_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void StudioWindow::updateMyCommentatorsList()
{
    shared_ptr<vector<CommentatorDTO>> coms_dto = commentator_repository->getCommentatorsDTOByOwnerId(studio_controller->getUser()->getId());
    my_coms_table_model = make_shared<CommentatorsTableModel>(coms_dto);
    ui->my_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->my_tableView->setModel(my_coms_table_model.get());
    for (int i = 0; i < my_coms_table_model->columnCount(); i++)
        ui->my_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void StudioWindow::updateStudiosList()
{
    shared_ptr<vector<StudioDTO>> studios_dto = studio_repository->getStudiosDTOByOwnerId(studio_controller->getUser()->getId());

    ui->my_studios_comboBox->clear();
    for (auto& studio : *studios_dto)
    {
        ui->my_studios_comboBox->addItem(QString::fromStdString(studio.getName()));
    }

    studios_table_model = make_shared<StudiosTableModel>(studios_dto);
    ui->studios_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->studios_tableView->setModel(studios_table_model.get());
    for (int i = 0; i < studios_table_model->columnCount(); i++)
        ui->studios_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void StudioWindow::updateLists()
{
    updateFreeCommentatorsList();
    updateMyCommentatorsList();
    updateStudiosList();
}


void StudioWindow::on_add_btn_clicked()
{
    try
    {
        QModelIndexList selectedRows = ui->free_tableView->selectionModel()->selectedRows();
        if (selectedRows.size() <= 0)
        {
            QMessageBox::information(this, "Error", "Выберите хотябы одного комментатора из списка свободных");
            return;
        }
        for(auto& ind : selectedRows)
        {
            int id = ui->free_tableView->model()->data(ind).toInt();
            shared_ptr<CommentatorBL> com_bl = commentator_repository->getCommentator(id);

            QString new_studio = ui->my_studios_comboBox->currentText();
            QModelIndex founded_index;
            int row_count = studios_table_model->rowCount();
            for (int i = 0; i < row_count; i++)
            {
                QModelIndex idx = studios_table_model->index(i, 3);
                if (studios_table_model->data(idx).toString() == new_studio)
                {
                   founded_index = studios_table_model->index(i, 0);
                   break;
                }
            }
            int new_studio_id = studios_table_model->data(founded_index).toInt();

            com_bl->getStudioId() = new_studio_id;
            commentator_repository->updateCommentator(*com_bl, id);
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


void StudioWindow::on_delete_btn_clicked()
{
    try
    {
        QModelIndexList selectedRows = ui->my_tableView->selectionModel()->selectedRows();
        if (selectedRows.size() <= 0)
        {
            QMessageBox::information(this, "Error", "Выберите хотябы одного вашего комментатора из списка");
            return;
        }
        for(auto& ind : selectedRows)
        {
            int id = ui->my_tableView->model()->data(ind).toInt();
            shared_ptr<CommentatorBL> com_bl = commentator_repository->getCommentator(id);

            com_bl->getStudioId() = 0;
            commentator_repository->updateCommentator(*com_bl, id);
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


void StudioWindow::on_free_tableView_clicked(const QModelIndex &index)
{
    ui->free_tableView->selectRow(index.row());
}


void StudioWindow::on_my_tableView_clicked(const QModelIndex &index)
{
    ui->my_tableView->selectRow(index.row());
}


void StudioWindow::on_studios_tableView_clicked(const QModelIndex &index)
{
    ui->studios_tableView->selectRow(index.row());
}

