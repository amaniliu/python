#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(QImage* img, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    if (img != nullptr)
        ui->view->addImage(img);

    connect(ui->btn_zoomin, SIGNAL(clicked()), ui->view, SLOT(zoomIn()));
    connect(ui->btn_zoomout, SIGNAL(clicked()), ui->view, SLOT(zoomOut()));
    connect(ui->btn_zoomorign, SIGNAL(clicked()), ui->view, SLOT(zoomOrigin()));
    connect(ui->btn_zoomfit, SIGNAL(clicked()), ui->view, SLOT(zoomAdjust()));
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}
