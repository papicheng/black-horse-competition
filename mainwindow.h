#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_sign_clicked();

    void on_pb_sign_back_clicked();

    void on_pb_my_rent_clicked();

    void on_pb_rent_back_clicked();

    void on_pb_mine_setting_clicked();


    void on_pb_mine_wirte_clicked();

    void on_pb_mine_back_clicked();

    void on_pb_home_message_clicked();

    void on_pb_message_back_clicked();

    void on_pb_pub_house_2_clicked();

    void on_cb_find_position_currentIndexChanged(int index);

    void on_cb_find_room_currentIndexChanged(int index);

    void on_cb_find_start_currentIndexChanged(int index);

    void on_cb_find_end_currentIndexChanged(int index);

    void on_cb_find_monye_currentIndexChanged(int index);

    void home_search();

    void find_search();

    void rent_search();

    void on_pb_pub_house_4_clicked();

    void on_cb_change_house_tpye_currentIndexChanged(int index);

    void on_cb_change_rental_currentIndexChanged(int index);

    void on_cb_change_position_currentIndexChanged(int index);

    void on_cb_change_mine_postion_currentIndexChanged(int index);

    void on_pb_pub_house_clicked();

public:
    long static UsePython(int a[5]);
private:
    Ui::MainWindow *ui;
};


QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);




#endif // MAINWINDOW_H
