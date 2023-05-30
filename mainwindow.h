#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QTableWidgetItem>

#include <iostream>
#include <fstream>
#include "./json.hpp"
#include <vector>

#include "travelagency.h"

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
    void on_actionEinlesen_triggered();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_tableWidget_2_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    TravelAgency interface;
};
#endif // MAINWINDOW_H
