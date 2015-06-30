// C/C++ Libraries
#include <iostream>

// Qt Libraries
//#include <QTextStream>
#include <QFileDialog>

// Local Libraries
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "segmentor.h"
#include "segmentationmetrics.h"


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_cloud(new pcl::PointCloud<pcl::PointXYZRGB>), // initialisation of the cloud
    m_viewer("Cloud Viewer")
{
    ui->setupUi(this);

    // setup connections
    connect(ui->btnFileBrowse, SIGNAL(clicked()), this, SLOT(loadPCDFile()));
    connect(ui->btnSegment, SIGNAL(clicked()), this, SLOT(segment()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPCDFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open PCD File"), "", tr("PCD Files (*.pcd)"));

    if(!filename.trimmed().isEmpty())
    {
        // clear the cloud
        m_cloud->clear();

        // load a new cloud
        ui->txtFilename->setText(filename);
        cout << "   File " << m_filename.toStdString() << " loaded" << endl;
        pcl::io::loadPCDFile ("D:/data/Laser/GTL_3 - Cloud.pcd", *m_cloud);

        if(m_cloud == 0)
        {
            cout << "Error: Failed to load file " << m_filename.toStdString() << endl;
        }
        else
        {
            cout << "   File " << m_filename.toStdString() << " loaded" << endl;
            cout << "   Point count " << m_cloud->points.size() << endl;
            cout << "----------------------------------------" << endl;
            m_viewer.showCloud(m_cloud);
        }
    }
}

void MainWindow::segment()
{
    m_filename = ui->txtFilename->text().toInt();
    m_knn = ui->txtKNN->text().toInt();
    m_smoothness_threshold = ui->txtSmoothness->text().toFloat();
    m_curvature_threshold = ui->txtCurvature->text().toFloat();
    m_min_cluster = ui->txtMinClusterSize->text().toInt();
    m_max_cluster = ui->txtMaxClusterSize->text().toInt();

    ui->txtResults->appendPlainText("----------------------------------------");
    ui->txtResults->appendPlainText("Parameters");
    ui->txtResults->appendPlainText("----------------------------------------");
    ui->txtResults->appendPlainText(QString("File name: %1").arg(m_filename));
    ui->txtResults->appendPlainText(QString("Smoothness threshold: %1").arg(m_smoothness_threshold));
    ui->txtResults->appendPlainText(QString("Curvature threshold: %1").arg(m_curvature_threshold));
    ui->txtResults->appendPlainText(QString("Min cluster size: %1").arg(m_min_cluster));
    ui->txtResults->appendPlainText(QString("Max cluster size: %1").arg(m_max_cluster));
    ui->txtResults->appendPlainText("----------------------------------------");

    // ------------------------------------------------------------
    //  Segment
    // ------------------------------------------------------------
    regionGrowingSegmentation();
}

void MainWindow::regionGrowingSegmentation()
{
    if(m_cloud == 0)
    {
        cout << "Error" << endl;
    }
    else
    {
        // ------------------------------------------------------------
        // segment the point cloud
        // ------------------------------------------------------------
        P::Segmentor segmentor;
        segmentor.setParameters(m_knn, m_smoothness_threshold, m_curvature_threshold, m_min_cluster, m_max_cluster);

        typedef pcl::search::Search<pcl::PointXYZRGB> SearchXYZRGB;
        typedef vector<pcl::PointIndices> vecPointIndeces;

        // --------------------------------------------
        // get the point normals
        SearchXYZRGB::Ptr tree = boost::shared_ptr<SearchXYZRGB> (new pcl::search::KdTree<pcl::PointXYZRGB>);
        P::Segmentor::NormalCloud::Ptr normals (new P::Segmentor::NormalCloud);
        segmentor.getNormals<const P::Segmentor::ColorCloud::ConstPtr &, pcl::PointXYZRGB, SearchXYZRGB::Ptr>(m_cloud, tree, normals);

        // --------------------------------------------
        // segment and extract segments (cluster)
        vecPointIndeces clusters;
        segmentor.getSegments<const P::Segmentor::ColorCloud::ConstPtr &, pcl::PointXYZRGB, SearchXYZRGB::Ptr, vecPointIndeces>(m_cloud, tree, normals, m_knn, clusters, m_colored_cloud);

        // --------------------------------------------
        // write the segments to a PCD file
        pcl::PCDWriter writer;
        writer.write("colouredcloud.pcd", *m_colored_cloud, false);

        // --------------------------------------------
        // get segment metrics
        P::SegmentationMetrics metrics;
        metrics.get<const P::Segmentor::ColorCloud::ConstPtr &, pcl::PointXYZRGB, vecPointIndeces>(m_cloud, normals, clusters);

        // --------------------------------------------
        // display the segmented point cloud
        m_viewer.showCloud(m_colored_cloud);
    }
}

void MainWindow::on_actionPoint_Cloud_triggered()
{
    m_viewer.showCloud(m_cloud);
}

void MainWindow::on_actionSegmented_Point_Cloud_triggered()
{
    m_viewer.showCloud(m_colored_cloud);
}
