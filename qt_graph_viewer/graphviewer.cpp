#include "graphviewer.hpp"
#include "ui_graphviewer.h"

GraphViewer::GraphViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphViewer)
{
    ui->setupUi(this);
}

GraphViewer::~GraphViewer()
{
    delete ui;
}
