#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Libraries
#include <QMainWindow>
#include <QString>

// PCL Libraries
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>

#include <pcl/visualization/cloud_viewer.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    /** \brief Set parameters
      * \param[in] to be explained
      */
    void setParameters(const int& knn,
                       const float& smoothness_threshold, const float& curvature_threshold,
                       const int& min_cluster_size, const int& max_cluster_size)
    {
        m_knn = knn;
        m_smoothness_threshold = smoothness_threshold;
        m_curvature_threshold = curvature_threshold;

        m_min_cluster = min_cluster_size;
        m_max_cluster = max_cluster_size;
    }

protected:
    void regionGrowingSegmentation();

public slots:
    void segment();

    void loadPCDFile();


private slots:
    void on_actionPoint_Cloud_triggered();

    void on_actionSegmented_Point_Cloud_triggered();

private:
    Ui::MainWindow *ui;

    QString m_filename;
    int m_knn; // neighborhood size

    float m_smoothness_threshold; // smoothness threshold ... in degrees
    float m_curvature_threshold; // curvature threshold ... in degress

    int m_min_cluster; // minimum cluster size
    int m_max_cluster; // maximum cluster size

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr m_cloud;

    pcl::PointCloud <pcl::PointXYZRGB>::Ptr m_colored_cloud;

    pcl::visualization::CloudViewer m_viewer;
};

#endif // MAINWINDOW_H
