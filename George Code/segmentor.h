#ifndef SEGMENTOR_H
#define SEGMENTOR_H

// C/C++ Libraries
#include <iostream>

// PCL Libraries
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/segmentation/region_growing.h>


namespace P {


class Segmentor
{
public:
    Segmentor();
    ~Segmentor();

    // type definitions
    typedef pcl::PointCloud<pcl::PointXYZRGBA> ColorACloud;
    typedef pcl::PointCloud<pcl::PointXYZRGB> ColorCloud;
    typedef pcl::PointCloud<pcl::PointXYZI> GrayCloud;
    typedef pcl::PointCloud<pcl::PointXYZ> MonochromeCloud;

    typedef pcl::PointCloud <pcl::Normal> NormalCloud;

    /** \brief Set parameters
      * \param[in] to be explained
      */
    void setParameters(const int& knn,
                       const float& smoothness_threshold, const float& curvature_threshold,
                       const int& min_cluster_size, const int& max_cluster_size);

    // --------------------------------------------
    // calculate the normals for the point cloud and store the normals in normalcloud
    template <class Cloud, class PointType, class Tree>
    void getNormals(Cloud &cloud, Tree &tree, NormalCloud::Ptr &normalcloud)
    {
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Computing Normals ..." << std::endl;

        pcl::NormalEstimation<PointType, pcl::Normal> normal_estimator;
        normal_estimator.setSearchMethod (tree);
        normal_estimator.setInputCloud (cloud);
        normal_estimator.setKSearch (m_knn);
        normal_estimator.compute (*normalcloud);

        std::cout << "Normals Computed ... " << normalcloud->points.size() << std::endl << std::endl;
    }

    // --------------------------------------------
    // perform the region growing segmentation
    template <class Cloud, class PointType, class Tree, class Indeces>
    void getSegments(Cloud &cloud, Tree &tree, NormalCloud::Ptr &normalcloud, int knn, Indeces &clusters,
                     pcl::PointCloud <pcl::PointXYZRGB>::Ptr &colored_cloud)
    {
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Extracting Segments ..." << std::endl;

        float smoothness_threshold = float(m_smoothness_threshold / 180.0 * M_PI);
        float curvature_threshold = float(m_curvature_threshold / 180.0 * M_PI);

        pcl::RegionGrowing<pcl::PointXYZRGB, pcl::Normal> reg;
        reg.setMinClusterSize (m_min_cluster);
        reg.setMaxClusterSize (m_max_cluster);
        reg.setSearchMethod (tree);
        reg.setNumberOfNeighbours (knn);
        reg.setInputCloud (cloud);
        //reg.setIndices (indices);
        reg.setInputNormals (normalcloud);
        reg.setSmoothnessThreshold (smoothness_threshold);
        reg.setCurvatureThreshold (curvature_threshold);

//        Indeces clusters;
        reg.extract (clusters);

        colored_cloud = reg.getColoredCloud ();
        std::cout << "Segments Extracted ... " << clusters.size () << std::endl << std::endl;
    }


private:
    int m_knn; // neighborhood size

    float m_smoothness_threshold; // smoothness threshold ... in degrees
    float m_curvature_threshold; // curvature threshold ... in degress

    int m_min_cluster; // minimum cluster size
    int m_max_cluster; // maximum cluster size
};


} // namespace

#endif // SEGMENTOR_H
