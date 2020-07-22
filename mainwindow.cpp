#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include"common.h"
#include"appsearchline.h"
#include"customtabstyle.h"
#include<Python.h>
#include"database.h"
#include<iostream>
#include<QMessageBox>
using namespace std;

int find_monye, find_position, find_room, find_time_start, find_time_end;//找房
int change_money, change_room, change_position, mine_position;
QString mine_position_str;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    int a[5] = {4500, 1, 3, 1, 1};
//    long result = UsePython(a);
//    qDebug()<< "result: "<< result;



    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    //    db.setDatabaseName("../ShareRenting/house_new.db");
    db.setDatabaseName("C:\\cbc\\house_new.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return;
    }
    //            QSqlQuery query(db);
    //            string sss = "select * from house where(community = \"同济新村\" or community = \"益华小区\"  )";
    //            query.exec( QString::fromStdString(sss));
    //            QSqlRecord rec = query.record();
    //            qDebug() << QObject::tr("house表字段数：" ) << rec.count();
    //            while(query.next())
    //            {
    //                for(int index = 0; index < 16; index++)
    //                    qDebug() << query.value(index) << " ";
    //                qDebug() << "\n";
    //            }


    //    DataBase d;
    //    d.createConnection();  //创建连接
    //    d.createTable();
    //    d.insert();
    //    d.queryAll();          //已经完成过createTable(), insert(), 现在进行查询


    connect(ui->le_search, SIGNAL(returnPressed()), this, SLOT(home_search()));
    connect(ui->le_find_house, SIGNAL(returnPressed()), this, SLOT(find_search()));
    connect(ui->le_search_biotope, SIGNAL(returnPressed()), this, SLOT(rent_search()));
    ui->stackedWidget_mine->setCurrentIndex(0);
    ui->stackedWidget_rent->setCurrentIndex(0);
    ui->stackedWidget_home->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);//首先显示首页
    QString house_rent_pic_path =  ":/images/img/享租logo - 图标.png";
    setWindowIcon(QIcon(house_rent_pic_path));//设置软件图标

    QString home_message_pic_path=  ":/images/img/消息.png";
    QImage home_message_img(home_message_pic_path);
    ui->lb_home_messege->setScaledContents(true);//图片等比例缩放
    ui->lb_home_messege->setPixmap(QPixmap::fromImage(home_message_img).scaled(ui->lb_home_messege->size(), Qt::KeepAspectRatio));

    QString home_search_pic_path=  ":/images/img/search.png";
    QImage home_search_img(home_search_pic_path);
    ui->lb_home_search_pic->setScaledContents(true);//图片等比例缩放
    ui->lb_home_search_pic->setPixmap(QPixmap::fromImage(home_search_img).scaled(ui->lb_home_search_pic->size(), Qt::KeepAspectRatio));


    ui->tabWidget->setStyleSheet("QTabBar:: tab{\
                                 background: transparent;\
            color:white;\
    min-width: 30ex;\
    min-height: 10ex;}\
QTabBar:: tab: hover{\
                   background:rgb(255, 255, 255, 100);}\
QTabBar:: tab: selected{\
                   border-color: white;\
background: white;\
color: green;}");//这个没有效果， 改不了tab的颜色
//    ui->tabWidget->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->cb_select_city->setStyleSheet("border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px; min-width: 4em; ");
//首页按钮设置
ui->pb_sign->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_change->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_zhuanqu->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_tuijian->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_gongyu->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_more->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");

QString sign_pic_path=  ":/images/img/签到.png";
QImage sign_img(sign_pic_path);
ui->lb_qiandao_pic->setScaledContents(true);//图片等比例缩放
ui->lb_qiandao_pic->setPixmap(QPixmap::fromImage(sign_img).scaled(ui->lb_qiandao_pic->size(), Qt::KeepAspectRatio));
//qDebug()<< sign_pic_path ;
QString change_pic_path=  ":/images/img/学生.png";
QImage change_img(change_pic_path);
ui->lb_huanfang_pic->setScaledContents(true);//图片等比例缩放
ui->lb_huanfang_pic->setPixmap(QPixmap::fromImage(change_img).scaled(ui->lb_huanfang_pic->size(), Qt::KeepAspectRatio));

QString special_pic_path=  ":/images/img/6_3职场晋升.png";
QImage special_img(special_pic_path);
ui->lb_zhuanqu_pic->setScaledContents(true);//图片等比例缩放
ui->lb_zhuanqu_pic->setPixmap(QPixmap::fromImage(special_img).scaled(ui->lb_zhuanqu_pic->size(), Qt::KeepAspectRatio));

QString recommend_pic_path=  ":/images/img/推荐.png";
QImage recommend_img(recommend_pic_path);
ui->lb_haofang_pic->setScaledContents(true);//图片等比例缩放
ui->lb_haofang_pic->setPixmap(QPixmap::fromImage(recommend_img).scaled(ui->lb_haofang_pic->size(), Qt::KeepAspectRatio));

QString department_pic_path=  ":/images/img/品质保证 Quality.png";
QImage department_img(department_pic_path);
ui->lb_gongyu_pic->setScaledContents(true);//图片等比例缩放
ui->lb_gongyu_pic->setPixmap(QPixmap::fromImage(department_img).scaled(ui->lb_gongyu_pic->size(), Qt::KeepAspectRatio));

QString more_pic_path=  ":/images/img/更多1.png";
QImage more_img(more_pic_path);
ui->lb_more_pic->setScaledContents(true);//图片等比例缩放
ui->lb_more_pic->setPixmap(QPixmap::fromImage(more_img).scaled(ui->lb_more_pic->size(), Qt::KeepAspectRatio));

QString hezu_pic_path=  ":/images/img/1.jpg";
QImage hezu_img(hezu_pic_path);
ui->lb_hezu_pic->setScaledContents(true);//图片等比例缩放
ui->lb_hezu_pic->setPixmap(QPixmap::fromImage(hezu_img).scaled(ui->lb_hezu_pic->size(), Qt::KeepAspectRatio));

QString hezhu2_pic_path=  ":/images/img/1.jpg";
QImage hezhu2_img(hezhu2_pic_path);
ui->lb_hezu_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_hezu_pic_2->setPixmap(QPixmap::fromImage(hezhu2_img).scaled(ui->lb_hezu_pic->size(), Qt::KeepAspectRatio));

ui->le_search->setStyleSheet("color:gray");//文本颜色

//签到
QString  sign_pic_path_1 = ":/images/img/红包1.png";
QImage sign_img_1(sign_pic_path_1);
ui->lb_sign_day_1->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_1->setPixmap(QPixmap::fromImage(sign_img_1).scaled(ui->lb_sign_day_1->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_2 =  ":/images/img/红包1.png";
QImage sign_img_2(sign_pic_path_2);
ui->lb_sign_day_2->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_2->setPixmap(QPixmap::fromImage(sign_img_2).scaled(ui->lb_sign_day_2->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_3 =  ":/images/img/红包1.png";
QImage sign_img_3(sign_pic_path_3);
ui->lb_sign_day_3->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_3->setPixmap(QPixmap::fromImage(sign_img_3).scaled(ui->lb_sign_day_3->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_4 =  ":/images/img/红包1.png";
QImage sign_img_4(sign_pic_path_4);
ui->lb_sign_day_4->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_4->setPixmap(QPixmap::fromImage(sign_img_4).scaled(ui->lb_sign_day_4->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_5 =  ":/images/img/红包1.png";
QImage sign_img_5(sign_pic_path_5);
ui->lb_sign_day_5->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_5->setPixmap(QPixmap::fromImage(sign_img_5).scaled(ui->lb_sign_day_5->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_6 =  ":/images/img/红包1.png";
QImage sign_img_6(sign_pic_path_6);
ui->lb_sign_day_6->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_6->setPixmap(QPixmap::fromImage(sign_img_6).scaled(ui->lb_sign_day_6->size(), Qt::KeepAspectRatio));


QString  sign_pic_path_7 =  ":/images/img/红包1.png";
QImage sign_img_7(sign_pic_path_7);
ui->lb_sign_day_7->setScaledContents(true);//图片等比例缩放
ui->lb_sign_day_7->setPixmap(QPixmap::fromImage(sign_img_7).scaled(ui->lb_sign_day_7->size(), Qt::KeepAspectRatio));

QString  sign_pic_path_ =  ":/images/img/gift.png";
QImage sign_img_(sign_pic_path_);
ui->lb_qiandao_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_qiandao_pic_2->setPixmap(QPixmap::fromImage(sign_img_).scaled(ui->lb_qiandao_pic_2->size(), Qt::KeepAspectRatio));


//消息
QString  message_pic_path_1_ =  ":/images/img/message1.jpg";
QImage message_img_1_(message_pic_path_1_);
message_img_1_ = message_img_1_.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

QString  message_pic_path_1 =  ":/images/img/boy1.jpg";
QImage message_img_1(message_pic_path_1);
QImage message1 = createImageWithOverlay(message_img_1, message_img_1_);
ui->lb_message_pic_1->setScaledContents(true);//图片等比例缩放
ui->lb_message_pic_1->setPixmap(QPixmap::fromImage(message1).scaled(ui->lb_message_pic_1->size(), Qt::KeepAspectRatio));

QString  message_pic_path_2 =  ":/images/img/boy2.png";
QImage message_img_2(message_pic_path_2);
QImage message2 = createImageWithOverlay(message_img_2, message_img_1_);
ui->lb_message_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_message_pic_2->setPixmap(QPixmap::fromImage(message2).scaled(ui->lb_message_pic_2->size(), Qt::KeepAspectRatio));

QString  message_pic_path_3 =  ":/images/img/girl1.jpg";
QImage message_img_3(message_pic_path_3);
//    QImage message3 = createImageWithOverlay(message_img_3, message_img_1_);
ui->lb_message_pic_3->setScaledContents(true);//图片等比例缩放
ui->lb_message_pic_3->setPixmap(QPixmap::fromImage(message_img_3).scaled(ui->lb_message_pic_3->size(), Qt::KeepAspectRatio));

QString  message_pic_path_4 =  ":/images/img/girl2.png";
QImage message_img_4(message_pic_path_4);
QImage message4 = createImageWithOverlay(message_img_4, message_img_1_);
ui->lb_message_pic_4->setScaledContents(true);//图片等比例缩放
ui->lb_message_pic_4->setPixmap(QPixmap::fromImage(message4).scaled(ui->lb_message_pic_4->size(), Qt::KeepAspectRatio));



//    ui->frame_message1->setStyleSheet("border:1px solid gray;");

//出租
ui->le_search_biotope->setStyleSheet("color:gray");//文本颜色
ui->cb_select_city_2->setStyleSheet("border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px; min-width: 4em; ");

ui->pb_my_rent->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_house_price->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
ui->pb_lease->setStyleSheet("border:2px groove gray;border-radius:6px;padding:2px 4px;background-color: #FFCC66;");
// 待加图片
QString  find_pic_path_1 = ":/images/img/1.jpg";
QImage find_img_1(find_pic_path_1);
ui->lb_find_pic_1->setScaledContents(true);//图片等比例缩放
ui->lb_find_pic_1->setPixmap(QPixmap::fromImage(find_img_1).scaled(ui->lb_find_pic_1->size(), Qt::KeepAspectRatio));

QString  find_pic_path_2 =  ":/images/img/1.jpg";
QImage find_img_2(find_pic_path_2);
ui->lb_find_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_find_pic_2->setPixmap(QPixmap::fromImage(find_img_2).scaled(ui->lb_find_pic_2->size(), Qt::KeepAspectRatio));

QString  find_pic_path_3 =  ":/images/img/1.jpg";
QImage find_img_3(find_pic_path_3);
ui->lb_find_pic_3->setScaledContents(true);//图片等比例缩放
ui->lb_find_pic_3->setPixmap(QPixmap::fromImage(find_img_3).scaled(ui->lb_find_pic_3->size(), Qt::KeepAspectRatio));

QString  find_pic_path_4 =  ":/images/img/1.jpg";
QImage find_img_4(find_pic_path_4);
ui->lb_find_pic_4->setScaledContents(true);//图片等比例缩放
ui->lb_find_pic_4->setPixmap(QPixmap::fromImage(find_img_4).scaled(ui->lb_find_pic_1->size(), Qt::KeepAspectRatio));

//找房
//    AppSearchLine* search = new AppSearchLine();
//    search->setParent(ui->widget);
QString find_path=  ":/images/img/search.png";
QImage find_img(find_path);
ui->lb_find_house_pic->setScaledContents(true);//图片等比例缩放
ui->lb_find_house_pic->setPixmap(QPixmap::fromImage(find_img).scaled(ui->lb_find_house_pic->size(), Qt::KeepAspectRatio));
ui->le_find_house->setStyleSheet("color:gray");//文本颜色
QString  list_path=  ":/images/img/list.jpg";
QImage list_img(list_path);
ui->lb_find_list_pic->setScaledContents(true);//图片等比例缩放
ui->lb_find_list_pic->setPixmap(QPixmap::fromImage(list_img).scaled(ui->lb_find_list_pic->size(), Qt::KeepAspectRatio));

QString  rentPath = ":/images/img/租.png";
QImage rentImg(rentPath);
ui->lb_rent_pic_1->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic_1->setPixmap(QPixmap::fromImage(rentImg).scaled(ui->lb_rent_pic_1->size(), Qt::KeepAspectRatio));

QString  rent_pic_path_2 = ":/images/img/租赁.png";
QImage rent_img_2(rent_pic_path_2);
ui->lb_rent_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic_2->setPixmap(QPixmap::fromImage(rent_img_2).scaled(ui->lb_rent_pic_2->size(), Qt::KeepAspectRatio));

QString  rent_pic_path_3 = ":/images/img/合同.png";
QImage rent_img_3(rent_pic_path_3);
ui->lb_rent_pic_3->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic_3->setPixmap(QPixmap::fromImage(rent_img_3).scaled(ui->lb_rent_pic_3->size(), Qt::KeepAspectRatio));

QString  rent_pic_path_6 = ":/images/img/1.jpg";
QImage rent_img_6(rent_pic_path_6);
ui->lb_rent_pic1->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic1->setPixmap(QPixmap::fromImage(rent_img_6).scaled(ui->lb_rent_pic1->size(), Qt::KeepAspectRatio));

QString  rent_pic_path_7 = ":/images/img/1.jpg";
QImage rent_img_7(rent_pic_path_7);
ui->lb_rent_pic2->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic2->setPixmap(QPixmap::fromImage(rent_img_7).scaled(ui->lb_rent_pic2->size(), Qt::KeepAspectRatio));

QString  rent_pic_path_8 = ":/images/img/1.jpg";
QImage rent_img_8(rent_pic_path_8);
ui->lb_rent_pic3->setScaledContents(true);//图片等比例缩放
ui->lb_rent_pic3->setPixmap(QPixmap::fromImage(rent_img_8).scaled(ui->lb_rent_pic3->size(), Qt::KeepAspectRatio));

//换房
QString  change_pic_path_1 = ":/images/img/1.jpg";
QImage change_img_1(change_pic_path_1);
ui->lb_change_pic_1->setScaledContents(true);//图片等比例缩放
ui->lb_change_pic_1->setPixmap(QPixmap::fromImage(change_img_1).scaled(ui->lb_change_pic_1->size(), Qt::KeepAspectRatio));

QString  change_pic_path_2 = ":/images/img/1.jpg";
QImage change_img_2(change_pic_path_2);
ui->lb_change_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_change_pic_2->setPixmap(QPixmap::fromImage(change_img_2).scaled(ui->lb_change_pic_2->size(), Qt::KeepAspectRatio));

QString  change_pic_path_3 = ":/images/img/1.jpg";
QImage change_img_3(change_pic_path_3);
ui->lb_change_pic_3->setScaledContents(true);//图片等比例缩放
ui->lb_change_pic_3->setPixmap(QPixmap::fromImage(change_img_3).scaled(ui->lb_change_pic_3->size(), Qt::KeepAspectRatio));


//我的
QIcon icon;
QString  setting_path =  ":/images/img/setting.png";
std::string str = setting_path.toStdString();
const char *mvFileName = str.c_str();
icon.addFile(tr(mvFileName));
ui->pb_mine_setting->setIcon(icon);

QString  mine_pic_path_1 = ":/images/img/girl2.png";
QImage mine_img_1(mine_pic_path_1);
ui->lb_mine_pic_1->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_1->setPixmap(QPixmap::fromImage(mine_img_1).scaled(ui->lb_mine_pic_1->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_2 = ":/images/img/合同 (2).png";
QImage mine_img_2(mine_pic_path_2);
ui->lb_mine_pic_2->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_2->setPixmap(QPixmap::fromImage(mine_img_2).scaled(ui->lb_mine_pic_2->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_3 =  ":/images/img/付款.png";
QImage mine_img_3(mine_pic_path_3);
ui->lb_mine_pic_3->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_3->setPixmap(QPixmap::fromImage(mine_img_3).scaled(ui->lb_mine_pic_3->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_4 = ":/images/img/评价.png";
QImage mine_img_4(mine_pic_path_4);
ui->lb_mine_pic_4->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_4->setPixmap(QPixmap::fromImage(mine_img_4).scaled(ui->lb_mine_pic_4->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_5 =  ":/images/img/售后.png";
QImage mine_img_5(mine_pic_path_5);
ui->lb_mine_pic_5->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_5->setPixmap(QPixmap::fromImage(mine_img_5).scaled(ui->lb_mine_pic_5->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_6 =  ":/images/img/银行卡.png";
QImage mine_img_6(mine_pic_path_6);
ui->lb_mine_pic_6->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_6->setPixmap(QPixmap::fromImage(mine_img_6).scaled(ui->lb_mine_pic_6->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_7 =  ":/images/img/钱.png";
QImage mine_img_7(mine_pic_path_7);
ui->lb_mine_pic_7->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_7->setPixmap(QPixmap::fromImage(mine_img_7).scaled(ui->lb_mine_pic_7->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_8 =  ":/images/img/维修.png";
QImage mine_img_8(mine_pic_path_8);
ui->lb_mine_pic_8->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_8->setPixmap(QPixmap::fromImage(mine_img_8).scaled(ui->lb_mine_pic_8->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_9 = ":/images/img/家庭保洁.png";
QImage mine_img_9(mine_pic_path_9);
ui->lb_mine_pic_9->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_9->setPixmap(QPixmap::fromImage(mine_img_9).scaled(ui->lb_mine_pic_9->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_10 =  ":/images/img/投诉.png";
QImage mine_img_10(mine_pic_path_10);
ui->lb_mine_pic_10->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_10->setPixmap(QPixmap::fromImage(mine_img_10).scaled(ui->lb_mine_pic_10->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_11 =  ":/images/img/隐私政策.png";
QImage mine_img_11(mine_pic_path_11);
ui->lb_mine_pic_11->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_11->setPixmap(QPixmap::fromImage(mine_img_11).scaled(ui->lb_mine_pic_11->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_12 =  ":/images/img/用户协议.png";
QImage mine_img_12(mine_pic_path_12);
ui->lb_mine_pic_12->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_12->setPixmap(QPixmap::fromImage(mine_img_12).scaled(ui->lb_mine_pic_12->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_13 =  ":/images/img/关于我们.png";
QImage mine_img_13(mine_pic_path_13);
ui->lb_mine_pic_13->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_13->setPixmap(QPixmap::fromImage(mine_img_13).scaled(ui->lb_mine_pic_13->size(), Qt::KeepAspectRatio));

QString  mine_pic_path_14 =  ":/images/img/girl2.png";
QImage mine_img_14(mine_pic_path_14);
ui->lb_mine_pic_14->setScaledContents(true);//图片等比例缩放
ui->lb_mine_pic_14->setPixmap(QPixmap::fromImage(mine_img_14).scaled(ui->lb_mine_pic_14->size(), Qt::KeepAspectRatio));

ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_sign_clicked()//签到
{
    ui->stackedWidget_home->setCurrentIndex(1);
}
//两张图合成一张图显示
QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage)
{
    QImage imageWithOverlay = QImage(baseImage.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&imageWithOverlay);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imageWithOverlay.rect(), Qt::transparent);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, baseImage);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(300, 0, overlayImage);

    painter.end();

    return imageWithOverlay;
}

void MainWindow::on_pb_sign_back_clicked()
{
    ui->stackedWidget_home->setCurrentIndex(0);
}

void MainWindow::on_pb_my_rent_clicked()//我要出租
{
    ui->stackedWidget_rent->setCurrentIndex(1);
}

void MainWindow::on_pb_rent_back_clicked()
{
    ui->stackedWidget_rent->setCurrentIndex(0);
}

void MainWindow::on_pb_mine_setting_clicked()//设置
{

}

void MainWindow::on_pb_mine_wirte_clicked()//编辑个人资料
{
    ui->stackedWidget_mine->setCurrentIndex(1);
}

void MainWindow::on_pb_mine_back_clicked()
{
    ui->stackedWidget_mine->setCurrentIndex(0);
}

void MainWindow::on_pb_home_message_clicked()
{
    ui->stackedWidget_home->setCurrentIndex(2);
}

void MainWindow::on_pb_message_back_clicked()
{
    ui->stackedWidget_home->setCurrentIndex(0);
}

void MainWindow::on_pb_pub_house_2_clicked()//  一键智能匹配
{
    if(ui->cb_find_position->currentIndex() == 0 || ui->cb_find_room->currentIndex() == 0 || ui->cb_find_start->currentIndex() == 0 || ui->cb_find_end->currentIndex() == 0 || ui->cb_find_monye->currentIndex() == 0) return;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    int money_left, money_right;
    switch(find_monye){
    case(1):
        money_left = 1500;
        money_right = 2500;
        break;
    case(2):
        money_left = 2500;
        money_right = 3500;
        break;
    case(3):
        money_left = 3500;
        money_right = 4500;
        break;
    case(4):
        money_left = 4500;
        money_right = 5500;
        break;
    case(5):
        money_left = 5500;
        money_right = 6500;
        break;
    case(6):
        money_left = 6500;
        money_right = 7500;
        break;
    case(7):
        money_left = 7500;
        money_right = 8500;
        break;
    case(8):
        money_left = 8500;
        money_right = 9500;
        break;
    default:
        break;
    }

    qDebug()<< find_position<< find_room << find_time_start << find_time_end<< money_left<< money_right;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("select * from house where(street = %1 and house_type_parameter = %2 and start_time <= %3 and end_time >= %4 and rental>= %5 and rental <= %6) ").arg(find_position).arg(find_room).arg(find_time_start).arg(find_time_end).arg(money_left).arg(money_right));

    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("house表字段数：" ) << rec.count();

    int count = 0;
    while(query.next())
    {
        count++;
        int id = query.value(0).toInt();
        QString city = query.value(1).toString();
        QString area = query.value(2).toString();
        int street_int = query.value(3).toInt();
        QString street;
        switch (street_int) {
        case(1):
            street = "鞍山";
            break;
        case(2):
            street = " 控江路";
            break;
        case(3):
            street = " 五角场";
            break;
        case(4):
            street = "新江湾城";
            break;
        case(5):
            street = "黄兴公园";
            break;
        case(6):
            street = " 东外滩";
            break;
        default:
            break;
        }
        QString community = query.value(4).toString();
        QString coordinate = query.value(5).toString();
        QString house_type = query.value(6).toString();
        int house_type_parameter = query.value(7).toInt();
        QString room = query.value(8).toString();
        int room_parameter = query.value(9).toInt();
        int acreage = query.value(10).toInt();
        int rental = query.value(11).toInt();
        QString traffic = query.value(12).toString();
        int traffic_convenience = query.value(13).toInt();
        int start_time = query.value(14).toInt();
        int end_time = query.value(15).toInt();

        //'price', 'room_num', 'transport', 'x_diff', 'y_diff'
        qDebug()<< "rental, room_parameter, traffic_convenience: "<< rental<< room_parameter<< traffic_convenience;
        //        int arr[5] = {rental, room_parameter, traffic_convenience, 1, 1};
        int a[5] = {1000, 2, 1, 0, 3};
        //        int * a = new int[5];
        //        a[0] = rental;
        //        a[1] = room_parameter;
        //        a[2] = traffic_convenience;
        //        a[3] = 1;
        //        a[4] = 1;
//        cout<<"11111111111111111111111111";
        long score = 4;
//        try {
//            score = UsePython(a);
//            cout<<"use python success!!!";
//        } catch (...) {
//            score = qrand() % 4 + 3;
//            cout<< "use python failed!!!";
//        }
//        cout<<"22222222222222222222";
        score = qrand() % 7 + 3;
        //        delete [] a;
        if(score == 0) score = 1;
        qDebug()<< "score: " << score;
        QString text_line_1 = house_type + "·" + community + "·" + room + "·" + QString::number(score) + "分";
        QString money_str = "￥" + QString::number(rental) + "/月起";
        QString str = area + "/" + street + "/" + QString::number(acreage)  + "㎡/近地铁/民水民电";
        QString  path = ":/images/img/" + QString::number(id % 100) + ".jpg";
        int remian_time_left , remian_time_right; //房屋剩余可租时间
        remian_time_left = qrand() % find_time_start + 1;
        remian_time_right = qrand() % (12 - find_time_end) + find_time_end + 1;
        if(remian_time_left > 12) remian_time_left = 12;
        if(remian_time_right > 12) remian_time_right = 12;
        QString left_str = "剩余" + QString::number(remian_time_left) + "-" + QString::number(remian_time_right) + "月 1个月起租";
        QImage img(path);
        if(count == 1) {
            ui->lb_text_1->setText(text_line_1);

            ui->lb_find_pic_1->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_1->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_1->size(), Qt::KeepAspectRatio));
            ui->lb_money_1->setText(money_str);
            ui->lb_show_1->setText(str);
            ui->lb_left_1->setText(left_str);
        }
        else if(count == 2){
            ui->lb_text_2->setText(text_line_1);
            ui->lb_find_pic_2->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_2->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_2->size(), Qt::KeepAspectRatio));
            ui->lb_money_2->setText(money_str);
            ui->lb_show_2->setText(str);
            ui->lb_left_2->setText(left_str);
        }
        else if(count == 3){
            ui->lb_text_3->setText(text_line_1);
            ui->lb_find_pic_3->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_3->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_3->size(), Qt::KeepAspectRatio));
            ui->lb_money_3->setText(money_str);
            ui->lb_show_3->setText(str);
            ui->lb_left_3->setText(left_str);
        }
        else if(count == 4){
            ui->lb_text_4->setText(text_line_1);
            ui->lb_find_pic_4->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_4->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_4->size(), Qt::KeepAspectRatio));
            ui->lb_money_4->setText(money_str);
            ui->lb_show_4->setText(str);
            ui->lb_left_4->setText(left_str);
        }

        for(int index = 0; index < 16; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    if(count < 1){
        ui->lb_text_1->clear();
        ui->lb_find_pic_1->clear();
        ui->lb_money_1->clear();
        ui->lb_show_1->clear();
        ui->lb_left_1->clear();

        ui->lb_text_2->clear();
        ui->lb_find_pic_2->clear();
        ui->lb_money_2->clear();
        ui->lb_show_2->clear();
        ui->lb_left_2->clear();

        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 2){
        ui->lb_text_2->clear();
        ui->lb_find_pic_2->clear();
        ui->lb_money_2->clear();
        ui->lb_show_2->clear();
        ui->lb_left_2->clear();

        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 3){
        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 4){
        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
}

void MainWindow::on_cb_find_position_currentIndexChanged(int index)
{
    find_position = index;
}

void MainWindow::on_cb_find_room_currentIndexChanged(int index)// 户型
{
    find_room = index - 1;
}

void MainWindow::on_cb_find_start_currentIndexChanged(int index)//起租时间
{
    find_time_start = index;
}

void MainWindow::on_cb_find_end_currentIndexChanged(int index)//到期时间
{
    find_time_end = index;
}

void MainWindow::on_cb_find_monye_currentIndexChanged(int index)//租金
{
    find_monye = index;
}
long MainWindow::UsePython(int a[5]){
    //qt 调用 python脚本，并传递参数
    //1.初始化python模
    Py_Initialize();
    long result = 0;
    if ( Py_IsInitialized() )
    {
        //2.导入*.py模块

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')");
        PyObject* pModule = PyImport_ImportModule("api");
        if (pModule) {
            // 创建元组设置参数
            //            a1, b1, c1, d1, e1, a2, b2, c2, d2, e2 = 1000, 2, 1, 0, 3, 1000, 2, 1, 0, 4
            PyObject* args = PyTuple_New(5);   // 2个参数
            PyObject* arg1 = PyLong_FromLong(a[0]);    // 参数一设为4
            PyObject* arg2 = PyLong_FromLong(a[1]);    // 参数二设为3
            PyObject* arg3 = PyLong_FromLong(a[2]);
            PyObject* arg4 = PyLong_FromLong(a[3]);
            PyObject* arg5 = PyLong_FromLong(a[4]);

            PyTuple_SetItem(args, 0, arg1);
            PyTuple_SetItem(args, 1, arg2);
            PyTuple_SetItem(args, 2, arg3);
            PyTuple_SetItem(args, 3, arg4);
            PyTuple_SetItem(args, 4, arg5);
            PyObject* pv = PyObject_GetAttrString(pModule, "score");
            // 调用函数
            PyObject* pRet = PyObject_CallObject(pv, args);

            // 创建元组设置参数
            //            PyObject* args = PyTuple_New(2);   // 2个参数
            //            args= Py_BuildValue("(i,i)",4,3);

            // 获取参数
            if (pRet)  // 验证是否调用成功
            {
                result = PyLong_AsLong(pRet);//返回整数
                qDebug() << "result:" << result;
            }
        }
        else{
            printf("Can't open python file!!!\n");
        }
    }
    Py_Finalize();
    return result;
}
void MainWindow::home_search(){
    //    int a[5] = {4500, 1, 3, 1, 1};
    //    long result = UsePython(a);
    //    qDebug()<< "result: "<< result;
    //    if(ui->cb_select_city->currentIndex() != 0 ){
    //        return;
    //    }

    ui->le_search->setStyleSheet("color:black;");
    QString str;
    str = ui->le_search->text();
    str = str.simplified();//去空格之类的
    int street = 0;
    if(str == "鞍山"){
        street = 1;
    }else if(str == "控江路"){
        street = 2;
    }else if(str == "五角场"){
        street = 3;
    }else if(str == "新江湾城"){
        street = 4;
    }else if(str == "黄兴公园"){
        street = 5;
    }else if(str == "东外滩"){
        street = 6;
    }
    qDebug()<< "street:"<< street;
    qDebug()<<"str: " << str;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    if(street == 0){
        string sss = "select * from house where(area =  \"" + str.toStdString() + "\" or street = \"" + str.toStdString() + "\" or community = \"" + str.toStdString() +"\")";
        //        qDebug() << "sss: "<< QString::fromStdString(sss);
        query.exec( QString::fromStdString(sss));
    }
    else{
        query.exec(QString("select * from house where street = %1").arg(street));
    }
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("house表字段数：" ) << rec.count();
    int count = 0;

    while(query.next())
    {
        count++;
        int id = query.value(0).toInt();
        QString city = query.value(1).toString();
        QString area = query.value(2).toString();
        int street_int = query.value(3).toInt();
        QString street;
        switch (street_int) {
        case(1):
            street = "鞍山";
            break;
        case(2):
            street = " 控江路";
            break;
        case(3):
            street = " 五角场";
            break;
        case(4):
            street = "新江湾城";
            break;
        case(5):
            street = "黄兴公园";
            break;
        case(6):
            street = " 东外滩";
            break;
        default:
            break;
        }
        QString community = query.value(4).toString();
        QString coordinate = query.value(5).toString();
        QString house_type = query.value(6).toString();
        int house_type_parameter = query.value(7).toInt();
        QString room = query.value(8).toString();
        int room_parameter = query.value(9).toInt();
        int acreage = query.value(10).toInt();
        int rental = query.value(11).toInt();
        QString traffic = query.value(12).toString();
        int traffic_convenience = query.value(13).toInt();
        int start_time = query.value(14).toInt();
        int end_time = query.value(15).toInt();

        //'price', 'room_num', 'transport', 'x_diff', 'y_diff'
        qDebug()<< "rental, room_parameter, traffic_convenience: "<< rental<< room_parameter<< traffic_convenience;

        QString text_line_1 = house_type + "·" + community + "·" + room;
        QString money_str = "￥" + QString::number(rental) + "/月起";
        QString str = area + "/" + street + "/" + QString::number(acreage)  + "㎡/近地铁/民水民电";
        QString  path = ":/images/img/" + QString::number(id % 100) + ".jpg";
        QImage img(path);
        if(count == 1) {
            ui->lb_home_text_1->setText(text_line_1);
            ui->lb_hezu_pic->setScaledContents(true);//图片等比例缩放
            ui->lb_hezu_pic->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_hezu_pic->size(), Qt::KeepAspectRatio));
            ui->lb_home_money_1->setText(money_str);
            ui->lb_home_show_1->setText(str);
        }
        else if(count == 2){
            ui->lb_home_text_2->setText(text_line_1);
            ui->lb_hezu_pic_2->setScaledContents(true);//图片等比例缩放
            ui->lb_hezu_pic_2->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_hezu_pic_2->size(), Qt::KeepAspectRatio));
            ui->lb_home_money_2->setText(money_str);
            ui->lb_home_show_2->setText(str);
        }
        else{
            break;
        }
        for(int index = 0; index < 16; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    ui->label_82->setText("1个月起租");
    ui->label_100->setText("1个月起租");
    if(count < 1){
        ui->lb_home_text_1->clear();
        ui->lb_hezu_pic->clear();
        ui->lb_home_money_1->clear();
        ui->lb_home_show_1->clear();
        ui->label_82->clear();

        ui->lb_home_text_2->clear();
        ui->lb_hezu_pic_2->clear();
        ui->lb_home_money_2->clear();
        ui->lb_home_show_2->clear();
        ui->label_100->clear();
    }
    else if(count < 2){
        ui->lb_home_text_2->clear();
        ui->lb_hezu_pic_2->clear();
        ui->lb_home_money_2->clear();
        ui->lb_home_show_2->clear();
        ui->label_100->clear();
    }
    for(int index = 0; index < 16; index++)
        qDebug() << query.value(index) << " ";
    qDebug() << "\n";
}
void MainWindow::find_search(){

    ui->le_find_house->setStyleSheet("color:black;");
    QString str;
    str = ui->le_find_house->text();
    str = str.simplified();//去空格之类的
    int street = 0;
    if(str == "鞍山"){
        street = 1;
    }else if(str == "控江路"){
        street = 2;
    }else if(str == "五角场"){
        street = 3;
    }else if(str == "新江湾城"){
        street = 4;
    }else if(str == "黄兴公园"){
        street = 5;
    }else if(str == "东外滩"){
        street = 6;
    }
    qDebug()<< "street:"<< street;
    qDebug()<<"str: " << str;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    if(street == 0){
        string sss = "select * from house where(area =  \"" + str.toStdString() + "\" or street = \"" + str.toStdString() + "\" or community = \"" + str.toStdString() +"\")";
        //        qDebug() << "sss: "<< QString::fromStdString(sss);
        query.exec( QString::fromStdString(sss));
    }
    else{
        query.exec(QString("select * from house where street = %1").arg(street));
    }
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("house表字段数：" ) << rec.count();
    int count = 0;

    while(query.next())
    {
        count++;
        int id = query.value(0).toInt();
        QString city = query.value(1).toString();
        QString area = query.value(2).toString();
        int street_int = query.value(3).toInt();
        QString street;
        switch (street_int) {
        case(1):
            street = "鞍山";
            break;
        case(2):
            street = "控江路";
            break;
        case(3):
            street = "五角场";
            break;
        case(4):
            street = "新江湾城";
            break;
        case(5):
            street = "黄兴公园";
            break;
        case(6):
            street = "东外滩";
            break;
        default:
            break;
        }
        QString community = query.value(4).toString();
        QString coordinate = query.value(5).toString();
        QString house_type = query.value(6).toString();
        int house_type_parameter = query.value(7).toInt();
        QString room = query.value(8).toString();
        int room_parameter = query.value(9).toInt();
        int acreage = query.value(10).toInt();
        int rental = query.value(11).toInt();
        QString traffic = query.value(12).toString();
        int traffic_convenience = query.value(13).toInt();
        int start_time = query.value(14).toInt();
        int end_time = query.value(15).toInt();

        //'price', 'room_num', 'transport', 'x_diff', 'y_diff'
        qDebug()<< "rental, room_parameter, traffic_convenience: "<< rental<< room_parameter<< traffic_convenience;

        QString text_line_1 = house_type + "·" + community + "·" + room;
        QString money_str = "￥" + QString::number(rental) + "/月起";
        QString str = area + "/" + street + "/" + QString::number(acreage)  + "㎡/近地铁/民水民电";
        QString  path = ":/images/img/" + QString::number(id % 100) + ".jpg";
        int left_time = qrand() % 7 + 1;
        int right_time = qrand() % (12 - left_time) + left_time + 1;
        QString leftStr = "剩余" + QString::number(left_time) + "-" + QString::number(right_time) + "月";
        QImage img(path);
        if(count == 1) {
            ui->lb_text_1->setText(text_line_1);
            ui->lb_find_pic_1->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_1->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_1->size(), Qt::KeepAspectRatio));
            ui->lb_money_1->setText(money_str);
            ui->lb_show_1->setText(str);
            ui->lb_left_1->setText(leftStr);
        }
        else if(count == 2){
            ui->lb_text_2->setText(text_line_1);
            ui->lb_find_pic_2->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_2->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_2->size(), Qt::KeepAspectRatio));
            ui->lb_money_2->setText(money_str);
            ui->lb_show_2->setText(str);
            ui->lb_left_2->setText(leftStr);
        }
        else if(count == 3){
            ui->lb_text_3->setText(text_line_1);
            ui->lb_find_pic_3->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_3->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_3->size(), Qt::KeepAspectRatio));
            ui->lb_money_3->setText(money_str);
            ui->lb_show_3->setText(str);
            ui->lb_left_3->setText(leftStr);
        }
        else if(count == 4){
            ui->lb_text_4->setText(text_line_1);
            ui->lb_find_pic_4->setScaledContents(true);//图片等比例缩放
            ui->lb_find_pic_4->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_find_pic_4->size(), Qt::KeepAspectRatio));
            ui->lb_money_4->setText(money_str);
            ui->lb_show_4->setText(str);
            ui->lb_left_4->setText(leftStr);
        }
        else{
            break;
        }
        for(int index = 0; index < 16; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    ui->label_82->setText("1个月起租");
    ui->label_100->setText("1个月起租");
    if(count < 1){
        ui->lb_text_1->clear();
        ui->lb_find_pic_1->clear();
        ui->lb_money_1->clear();
        ui->lb_show_1->clear();
        ui->lb_left_1->clear();

        ui->lb_text_2->clear();
        ui->lb_find_pic_2->clear();
        ui->lb_money_2->clear();
        ui->lb_show_2->clear();
        ui->lb_left_2->clear();

        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 2){
        ui->lb_text_2->clear();
        ui->lb_find_pic_2->clear();
        ui->lb_money_2->clear();
        ui->lb_show_2->clear();
        ui->lb_left_2->clear();

        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 3){
        ui->lb_text_3->clear();
        ui->lb_find_pic_3->clear();
        ui->lb_money_3->clear();
        ui->lb_show_3->clear();
        ui->lb_left_3->clear();

        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    else if(count < 4){
        ui->lb_text_4->clear();
        ui->lb_find_pic_4->clear();
        ui->lb_money_4->clear();
        ui->lb_show_4->clear();
        ui->lb_left_4->clear();
    }
    for(int index = 0; index < 16; index++)
        qDebug() << query.value(index) << " ";
    qDebug() << "\n";
    query.finish();
}
void MainWindow::on_pb_pub_house_4_clicked()// 一键智能交换
{
    if(ui->cb_change_mine_postion->currentIndex() == 0 || ui->cb_change_house_tpye->currentIndex() == 0 || ui->cb_change_rental->currentIndex() == 0 || ui->cb_change_position->currentIndex() == 0 ) return;
    int change_start_time = ui->le_change_start->text().toInt();
    int change_end_time = ui->le_change_end->text().toInt();
    qDebug()<< "change start: "<< change_start_time << " end: "<< change_end_time;
    if(change_end_time > 12 ||change_end_time < 1 || change_start_time > 12 || change_start_time < 1) return;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    int money_left, money_right;
    switch(change_money){
    case(1):
        money_left = 1500;
        money_right = 2500;
        break;
    case(2):
        money_left = 2500;
        money_right = 3500;
        break;
    case(3):
        money_left = 3500;
        money_right = 4500;
        break;
    case(4):
        money_left = 4500;
        money_right = 5500;
        break;
    case(5):
        money_left = 5500;
        money_right = 6500;
        break;
    case(6):
        money_left = 6500;
        money_right = 7500;
        break;
    case(7):
        money_left = 7500;
        money_right = 8500;
        break;
    case(8):
        money_left = 8500;
        money_right = 9500;
        break;
    default:
        break;
    }
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec(QString("select * from house where(street = %1 and house_type_parameter = %2 and start_time <= %3 and end_time >= %4 and rental>= %5 and rental <= %6) ").arg(change_position).arg(change_room).arg(change_start_time).arg(change_end_time).arg(money_left).arg(money_right));
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("house表字段数：" ) << rec.count();

    int count = 0;
    while(query.next())
    {
        count++;
        int id = query.value(0).toInt();
        QString city = query.value(1).toString();
        QString area = query.value(2).toString();
        int street_int = query.value(3).toInt();
        QString street;
        switch (street_int) {
        case(1):
            street = "鞍山";
            break;
        case(2):
            street = " 控江路";
            break;
        case(3):
            street = " 五角场";
            break;
        case(4):
            street = "新江湾城";
            break;
        case(5):
            street = "黄兴公园";
            break;
        case(6):
            street = " 东外滩";
            break;
        default:
            break;
        }
        QString community = query.value(4).toString();
        QString coordinate = query.value(5).toString();
        QString house_type = query.value(6).toString();
        int house_type_parameter = query.value(7).toInt();
        QString room = query.value(8).toString();
        int room_parameter = query.value(9).toInt();
        int acreage = query.value(10).toInt();
        int rental = query.value(11).toInt();
        QString traffic = query.value(12).toString();
        int traffic_convenience = query.value(13).toInt();
        int start_time = query.value(14).toInt();
        int end_time = query.value(15).toInt();
        //'price', 'room_num', 'transport', 'x_diff', 'y_diff'
        qDebug()<< "rental, room_parameter, traffic_convenience: "<< rental<< room_parameter<< traffic_convenience;
        //        int arr[5] = {rental, room_parameter, traffic_convenience, 1, 1};
        //        int a[5] = {1000, 2, 1, 0, 3};
        int * a = new int[5];
        a[0] = rental;
        a[1] = room_parameter;
        a[2] = traffic_convenience;
        a[3] = 1;
        a[4] = 1;
        //        long score = UsePython(a);
        long score = qrand() % 7 +3;
        if(score == 0) score = 1;
        qDebug()<< "score: " << score;
        QString text_line_1 = house_type + "·" + community + "·" + room + "·" + QString::number(score) + "分";
        QString money_str = "￥" + QString::number(rental) + "/月起";
        QString str = area + "/" + street + "/" + QString::number(acreage)  + "㎡/近地铁/民水民电";
        QString  path = ":/images/img/" + QString::number(id % 100) + ".jpg";

        int remian_time_left , remian_time_right; //房屋剩余可租时间
        remian_time_left = qrand() % change_start_time + 1;
        remian_time_right = qrand() % (12 - change_end_time) + change_end_time + 1;
        if(remian_time_left > 12) remian_time_left = 12;
        if(remian_time_right > 12) remian_time_right = 12;

        QString left_str = "期望交换位置：" + mine_position_str;
        QImage img(path);

        if(count == 1) {
            ui->lb_change_text_1->setText(text_line_1);
            ui->lb_change_pic_1->setScaledContents(true);//图片等比例缩放
            ui->lb_change_pic_1->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_change_pic_1->size(), Qt::KeepAspectRatio));
            ui->lb_change_money_1->setText(money_str);
            ui->lb_change_middle_1->setText(str);
            ui->lb_to_1->setText(left_str);
        }
        else if(count == 2){
            ui->lb_change_text_2->setText(text_line_1);
            ui->lb_change_pic_2->setScaledContents(true);//图片等比例缩放
            ui->lb_change_pic_2->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_change_pic_2->size(), Qt::KeepAspectRatio));
            ui->lb_change_money_2->setText(money_str);
            ui->lb_change_middle_2->setText(str);
            ui->lb_to_2->setText(left_str);
        }
        else if(count == 3){
            ui->lb_change_text_3->setText(text_line_1);
            ui->lb_change_pic_3->setScaledContents(true);//图片等比例缩放
            ui->lb_change_pic_3->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_change_pic_3->size(), Qt::KeepAspectRatio));
            ui->lb_change_money_3->setText(money_str);
            ui->lb_change_middle_3->setText(str);
            ui->lb_to_3->setText(left_str);
        }

        for(int index = 0; index < 16; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    if(count < 1){
        ui->lb_change_text_1->clear();
        ui->lb_change_pic_1->clear();
        ui->lb_change_money_1->clear();
        ui->lb_change_middle_1->clear();
        ui->lb_to_1->clear();

        ui->lb_change_text_2->clear();
        ui->lb_change_pic_2->clear();
        ui->lb_change_money_2->clear();
        ui->lb_change_middle_2->clear();
        ui->lb_to_2->clear();

        ui->lb_change_text_3->clear();
        ui->lb_change_pic_3->clear();
        ui->lb_change_money_3->clear();
        ui->lb_change_middle_3->clear();
        ui->lb_to_3->clear();
    }
    else if(count < 2){
        ui->lb_change_text_2->clear();
        ui->lb_change_pic_2->clear();
        ui->lb_change_money_2->clear();
        ui->lb_change_middle_2->clear();
        ui->lb_to_2->clear();

        ui->lb_change_text_3->clear();
        ui->lb_change_pic_3->clear();
        ui->lb_change_money_3->clear();
        ui->lb_change_middle_3->clear();
        ui->lb_to_3->clear();
    }
    else if(count < 3){
        ui->lb_change_text_3->clear();
        ui->lb_change_pic_3->clear();
        ui->lb_change_money_3->clear();
        ui->lb_change_middle_3->clear();
        ui->lb_to_3->clear();
    }
    query.finish();
}

void MainWindow::on_cb_change_house_tpye_currentIndexChanged(int index)
{
    change_room = index - 1;
}

void MainWindow::on_cb_change_rental_currentIndexChanged(int index)
{
    change_money = index;
}

void MainWindow::on_cb_change_position_currentIndexChanged(int index)
{
    change_position = index;
}

void MainWindow::on_cb_change_mine_postion_currentIndexChanged(int index)
{
    mine_position = index;
    switch (mine_position) {
    case(1):
        mine_position_str = "鞍山";
        break;
    case(2):
        mine_position_str = " 控江路";
        break;
    case(3):
        mine_position_str = " 五角场";
        break;
    case(4):
        mine_position_str = "新江湾城";
        break;
    case(5):
        mine_position_str = "黄兴公园";
        break;
    case(6):
        mine_position_str = " 东外滩";
        break;
    default:
        break;
    }
}
void MainWindow::rent_search(){

    ui->le_search_biotope->setStyleSheet("color:black;");
    QString str;
    str = ui->le_search_biotope->text();
    str = str.simplified();//去空格之类的
    int street = 0;
    if(str == "鞍山"){
        street = 1;
    }else if(str == "控江路"){
        street = 2;
    }else if(str == "五角场"){
        street = 3;
    }else if(str == "新江湾城"){
        street = 4;
    }else if(str == "黄兴公园"){
        street = 5;
    }else if(str == "东外滩"){
        street = 6;
    }
    qDebug()<< "street:"<< street;
    qDebug()<<"str: " << str;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    if(street == 0){
        string sss = "select * from house where(area =  \"" + str.toStdString() + "\" or street = \"" + str.toStdString() + "\" or community = \"" + str.toStdString() +"\")";
        //        qDebug() << "sss: "<< QString::fromStdString(sss);
        query.exec( QString::fromStdString(sss));
    }
    else{
        query.exec(QString("select * from house where street = %1").arg(street));
    }
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("house表字段数：" ) << rec.count();
    int count = 0;

    while(query.next())
    {
        count++;
        int id = query.value(0).toInt();
        QString city = query.value(1).toString();
        QString area = query.value(2).toString();
        int street_int = query.value(3).toInt();
        QString street;
        switch (street_int) {
        case(1):
            street = "鞍山";
            break;
        case(2):
            street = " 控江路";
            break;
        case(3):
            street = " 五角场";
            break;
        case(4):
            street = "新江湾城";
            break;
        case(5):
            street = "黄兴公园";
            break;
        case(6):
            street = " 东外滩";
            break;
        default:
            break;
        }
        QString community = query.value(4).toString();
        QString coordinate = query.value(5).toString();
        QString house_type = query.value(6).toString();
        int house_type_parameter = query.value(7).toInt();
        QString room = query.value(8).toString();
        int room_parameter = query.value(9).toInt();
        int acreage = query.value(10).toInt();
        int rental = query.value(11).toInt();
        QString traffic = query.value(12).toString();
        int traffic_convenience = query.value(13).toInt();
        int start_time = query.value(14).toInt();
        int end_time = query.value(15).toInt();

        //'price', 'room_num', 'transport', 'x_diff', 'y_diff'
        qDebug()<< "rental, room_parameter, traffic_convenience: "<< rental<< room_parameter<< traffic_convenience;
        QString text_line_1 = house_type + "·" + community + "·" + room;
        QString money_str = "￥" + QString::number(rental) + "/月起";
        QString str = area + "/" + street + "/" + QString::number(acreage)  + "㎡/近地铁/民水民电";
        QString  path = ":/images/img/" + QString::number(id % 100) + ".jpg";
        QImage img(path);
        if(count == 1) {
            ui->lb_rent_text_1->setText(text_line_1);
            ui->lb_rent_pic1->setScaledContents(true);//图片等比例缩放
            ui->lb_rent_pic1->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_rent_pic1->size(), Qt::KeepAspectRatio));
            ui->lb_rent_money_1->setText(money_str);
            ui->lb_rent_show_1->setText(str);
            ui->lb_one_month_1->setText("1个月起租");
        }
        else if(count == 2){
            ui->lb_rent_text_2->setText(text_line_1);
            ui->lb_rent_pic2->setScaledContents(true);//图片等比例缩放
            ui->lb_rent_pic2->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_rent_pic2->size(), Qt::KeepAspectRatio));
            ui->lb_rent_money_2->setText(money_str);
            ui->lb_rent_show_2->setText(str);
            ui->lb_one_month_2->setText("1个月起租");
        }
        else if(count == 3){
            ui->lb_rent_text_3->setText(text_line_1);
            ui->lb_rent_pic3->setScaledContents(true);//图片等比例缩放
            ui->lb_rent_pic3->setPixmap(QPixmap::fromImage(img).scaled(ui->lb_rent_pic3->size(), Qt::KeepAspectRatio));
            ui->lb_rent_money_3->setText(money_str);
            ui->lb_rent_show_3->setText(str);
            ui->lb_one_month_3->setText("1个月起租");
        }
        else{
            break;
        }
        for(int index = 0; index < 16; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }

    if(count < 1){
        ui->lb_rent_text_1->clear();
        ui->lb_rent_pic1->clear();
        ui->lb_rent_money_1->clear();
        ui->lb_rent_show_1->clear();
        ui->lb_one_month_1->clear();

        ui->lb_rent_text_2->clear();
        ui->lb_rent_pic2->clear();
        ui->lb_rent_money_2->clear();
        ui->lb_rent_show_2->clear();
        ui->lb_one_month_2->clear();

        ui->lb_rent_text_3->clear();
        ui->lb_rent_pic3->clear();
        ui->lb_rent_money_3->clear();
        ui->lb_rent_show_3->clear();
        ui->lb_one_month_3->clear();
    }
    else if(count < 2){
        ui->lb_rent_text_2->clear();
        ui->lb_rent_pic2->clear();
        ui->lb_rent_money_2->clear();
        ui->lb_rent_show_2->clear();
        ui->lb_one_month_2->clear();

        ui->lb_rent_text_3->clear();
        ui->lb_rent_pic3->clear();
        ui->lb_rent_money_3->clear();
        ui->lb_rent_show_3->clear();
        ui->lb_one_month_3->clear();
    }
    else if(count < 3){
        ui->lb_rent_text_3->clear();
        ui->lb_rent_pic3->clear();
        ui->lb_rent_money_3->clear();
        ui->lb_rent_show_3->clear();
        ui->lb_one_month_3->clear();
    }
    for(int index = 0; index < 16; index++)
        qDebug() << query.value(index) << " ";
    qDebug() << "\n";

    query.finish();
}

void MainWindow::on_pb_pub_house_clicked()//发布房源
{
    QString city = "上海";
    QString area = "杨浦";
    QString street_str = ui->le_rent_mess_1->text();
    int street;
    if(street_str == "鞍山") street = 1;
    else if(street_str == "控江路") street = 2;
    else if(street_str == "五角场") street = 3;
    else if(street_str == "新江湾城") street = 4;
    else if(street_str == "黄兴公园") street = 5;
    else if(street_str == "东外滩") street = 6;
    else street = 7;
    QString community = ui->le_rent_mess_2->text();
    QString coordinate = QString::number(qrand() % 4 + 1) + "," + QString::number(qrand() % 4 + 1);
    QString room = ui->le_rent_mess_3->text();
    int room_parameter = 1;//room.toStdString()[0]; //++++++++++++++++++++++
    QString house_type = ui->le_rent_mess_4->text();
    int house_type_parameter;
    if(house_type == "合租") house_type_parameter = 1;
    else house_type_parameter = 0;
    int acreage = ui->le_rent_mess_5->text().toInt();
    int start_time = ui->le_rent_mess_6->text().toInt();
    int end_time = ui->le_rent_mess_7->text().toInt();
    int  rental = ui->le_rent_mess_8->text().toInt();
    int line = ui->le_line->text().toInt();
    int distance = ui->le_distance->text().toInt();
    QString traffic = "距离地铁" + QString::number(line) + "号线" + QString::number(distance) + "米";
    int traffic_convenience;
    if(distance <= 400) traffic_convenience = 4;
    else if(distance <=  700) traffic_convenience = 3;
    else if(distance <= 1000) traffic_convenience = 2;
    else traffic_convenience = 1;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select count() from house");
    int id = 101;
    while(query.next())
    {
        id = query.value(0).toInt() + 1;
    }
    query.finish();
    qDebug()<<"id: "<<id;
    query.prepare("insert into house values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    //    QVariantList list;
    qDebug()<< id << city<< area<< street<<community<<coordinate<<house_type<<house_type_parameter<<room<<room_parameter<<acreage<<rental<<traffic<<traffic_convenience<<start_time<<end_time;

    //    query.addBindValue(list);
    //    if (!query.execBatch()) {
    //        QMessageBox::critical(0, QObject::tr("Database Error"),
    //                              query.lastError().text());
    //    }
    query.bindValue(0,id);
    query.bindValue(1,city);
    query.bindValue(2,area);
    query.bindValue(3,street);
    query.bindValue(4,community);
    query.bindValue(5,coordinate);
    query.bindValue(6,house_type);
    query.bindValue(7,house_type_parameter);
    query.bindValue(8,room);
    query.bindValue(9,room_parameter);
    query.bindValue(10,acreage);
    query.bindValue(11,rental);
    query.bindValue(12,traffic);
    query.bindValue(13,traffic_convenience);
    query.bindValue(14,start_time);
    query.bindValue(15,end_time);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
    }
    query.finish();
}
