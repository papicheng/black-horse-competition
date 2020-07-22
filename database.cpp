#include "database.h"

//建立一个数据库连接
bool DataBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//house.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}

//创建数据库表
bool DataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table house(id int primary key,city varchar,"
                              "area varchar,street int,"
                              "community varchar,coordinate varchar,house_type varchar,"
                              "house_type_parameter int, room varchar,"
                              "room_parameter int, acreage int, "
                              "rental int, traffic varchar, "
                              "traffic_convenience int, start_time int, end_time int)");
    if(success)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

//向数据库中插入记录
bool DataBase::insert()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into house values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.bindValue(0,1);query.bindValue(1,"上海");query.bindValue(2,"杨浦");query.bindValue(3,1);query.bindValue(4,"同济新村");query.bindValue(5,"1，1");query.bindValue(6,"合租");query.bindValue(7,1);query.bindValue(8,"2居室·南卧");query.bindValue(9,2);query.bindValue(10,15);query.bindValue(11,3200);query.bindValue(12,"距地铁10号线200米"); query.bindValue(13,4);query.bindValue(14,1);query.bindValue(15,12);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,2);query.bindValue(1,"上海");query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"同济新村"); query.bindValue(5,"1，1"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"2居室·北卧"); query.bindValue(9,2); query.bindValue(10,15); query.bindValue(11,3000); query.bindValue(12,"距地铁10号线200米"); query.bindValue(13,4); query.bindValue(14,1); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,3); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"抚顺路363弄"); query.bindValue(5,"1，2"); query.bindValue(6,"整租"); query.bindValue(7,0); query.bindValue(8,"2室1厅"); query.bindValue(9,2); query.bindValue(10,48); query.bindValue(11,5300); query.bindValue(12,"距地铁10号线500米"); query.bindValue(13,3); query.bindValue(14,1); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,4); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"鞍山八村"); query.bindValue(5,"1，3"); query.bindValue(6,"整租"); query.bindValue(7,0); query.bindValue(8,"1室1厅"); query.bindValue(9,1); query.bindValue(10,40); query.bindValue(11,4500); query.bindValue(12,"距地铁10号线500米"); query.bindValue(13,3); query.bindValue(14,1); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,5); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"鞍山六村"); query.bindValue(5,"1，4"); query.bindValue(6,"整租"); query.bindValue(7,0); query.bindValue(8,"1室0厅"); query.bindValue(9,1); query.bindValue(10,34); query.bindValue(11,4000); query.bindValue(12,"距地铁8号线600米"); query.bindValue(13,3); query.bindValue(14,3); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,6); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,2); query.bindValue(4,"凤城六村"); query.bindValue(5,"2，1"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"2居室·南卧"); query.bindValue(9,2); query.bindValue(10,9); query.bindValue(11,2630); query.bindValue(12,"距地铁8号线600米"); query.bindValue(13,3); query.bindValue(14,3); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,7); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,2); query.bindValue(4,"凤城六村"); query.bindValue(5,"2，1"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"2居室·南卧"); query.bindValue(9,2); query.bindValue(10,9); query.bindValue(11,2630); query.bindValue(12,"距地铁8号线600米"); query.bindValue(13,3); query.bindValue(14,3); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,8); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"国康公寓"); query.bindValue(5,"2，2"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"4居室·南卧"); query.bindValue(9,4); query.bindValue(10,15); query.bindValue(11,2800); query.bindValue(12,"距地铁10号线800米"); query.bindValue(13,2); query.bindValue(14,4); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,9); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"国康公寓"); query.bindValue(5,"2，2"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"4居室·南卧"); query.bindValue(9,4); query.bindValue(10,15); query.bindValue(11,2800); query.bindValue(12,"距地铁10号线800米"); query.bindValue(13,2); query.bindValue(14,4); query.bindValue(15,12);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    query.bindValue(0,10); query.bindValue(1,"上海"); query.bindValue(2,"杨浦"); query.bindValue(3,1); query.bindValue(4,"国康公寓"); query.bindValue(5,"2，2"); query.bindValue(6,"合租"); query.bindValue(7,1); query.bindValue(8,"4居室·北卧"); query.bindValue(9,4); query.bindValue(10,15); query.bindValue(11,2600); query.bindValue(12,"距地铁10号线800米"); query.bindValue(13,2); query.bindValue(14,3); query.bindValue(15,9);
    success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }

    //    long records = 10;
    //    for(int i=0; i<records; i++)
    //    {
    //        query.bindValue(0, i);
    //        query.bindValue(1, "四轮");
    //        query.bindValue(2, "轿车");
    //        query.bindValue(3, "富康");
    //        query.bindValue(4, rand()%100);
    //        query.bindValue(5, rand()%10000);
    //        query.bindValue(6, rand()%300);
    //        query.bindValue(7, rand()%200000);
    //        query.bindValue(8, rand()%52);
    //        query.bindValue(9, rand()%100);

    //        bool success=query.exec();
    //        if(!success)
    //        {
    //            QSqlError lastError = query.lastError();
    //            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
    //            return false;
    //        }
    //    }
    return true;
}

//查询所有信息
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from house");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("automobil表字段数：" ) << rec.count();

    while(query.next())
    {
        for(int index = 0; index < 10; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
    return true;
}

//根据ID删除记录
bool DataBase::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("delete from house where id = %1").arg(id));
    if(!query.exec())
    {
        qDebug() << "删除记录失败！";
        return false;
    }
    return true;
}

//根据ID更新记录
bool DataBase::updateById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("update automobil set attribute=?,type=?,"
                          "kind=?, nation=?,"
                          "carnumber=?, elevaltor=?,"
                          "distance=?, oil=?,"
                          "temperature=? where id=%1").arg(id));

    query.bindValue(0,"四轮");
    query.bindValue(1,"轿车");
    query.bindValue(2,"富康");
    query.bindValue(3,rand()%100);
    query.bindValue(4,rand()%10000);
    query.bindValue(5,rand()%300);
    query.bindValue(6,rand()%200000);
    query.bindValue(7,rand()%52);
    query.bindValue(8,rand()%100);

    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
    }
    return true;
}

//排序
bool DataBase::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from automobil order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("排序失败！");
        return false;
    }
}
