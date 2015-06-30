// C/C++ Libraries
#include <vector>
#include <string>
//#include <cmath>

// PCL Libraries
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
//#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>

// Local Libraries
#include "segmentationmetrics.h"


namespace P {


SegmentationMetrics::SegmentationMetrics()
{

}

SegmentationMetrics::~SegmentationMetrics()
{

}

// --------------------------------------------
// get curvature metrics
void SegmentationMetrics::getCurvatureMetrics(NormalCloud::Ptr &normalcloud)/*const int& segcount, const double& df,
                                              NormalCloud::Ptr &normalcloud,
                                              const double& feature_average,
                                              const double& N, const double& N_abs)*/
{
    double sum = 0.0;
    double dev_sum = 0.0;
    double npss_sum = 0.0;
    double yang_sum = 0.0;

    for(int segindex = 0; segindex < segcount; ++segindex)
    {
        stringstream filename_normals;
        filename_normals << "normals/segment_" << segindex << ".pcd";
        //std::cout<<"points on segment_"<<num_seg<<std::endl;

        pcl::PointCloud<pcl::Normal>::Ptr normalcloud_seg (new pcl::PointCloud<pcl::Normal>);
        if (pcl::io::loadPCDFile<pcl::Normal> (filename_normals.str(), *normalcloud_seg) == -1)
        {
            PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
        }
        else
        {
            double mean_f = compute_average(normalcloud_seg->points.size(), normalcloud_seg);// mean feature value for the segment
            double variance = compute_v(mean_f, normalcloud_seg);
            double abs_deviation = compute_abs(mean_f, normalcloud_seg->points.size(), normalcloud_seg);

            //computing
            double max_v = (df * df) / 2.0;

            sum += ((normalcloud_seg->points.size() * variance) / N);
            dev_sum += ((normalcloud_seg->points.size() * abs_deviation) / N_abs);
            ///////////////////////////////////////////////////////////////////////////////////
            double npss_var;

            npss_var = normalcloud_seg->points.size() * (feature_average - mean_f) * (feature_average - mean_f);
            npss_sum += npss_var;
            /////////////////////////////////////////////////////////////////////
        }
    }

    double yang_function = yang_sum;
    double point_var = compute_v(feature_average, normalcloud); //point variance
    double seg_stddev = sqrt(npss_sum / (normalcloud->points.size() * point_var));

    m_metrics.sum = sum;
    m_metrics.seg_stddev = seg_stddev;
    m_metrics.NPSS = 1.0 - seg_stddev;
    m_metrics.IntraRegionUniformity = 1.0 - sum;
    m_metrics.AverageAbsoluteDeviation = 1.0 - dev_sum;
    m_metrics.CurvatureHeterogeneity = m_metrics.sum / segcount;
    m_metrics.P = (m_metrics.seg_stddev + 1) / (m_metrics.sum + m_metrics.seg_stddev + 1);

    cout << "--------------------------------------------" << endl;
    cout << "Curvature Metrics" << endl;
    cout << "NPSS = " << m_metrics.NPSS << endl;
    cout << "Curvature: Intra Region Uniformity = " << m_metrics.IntraRegionUniformity << endl;
    cout << "Curvature: Average Absolute Deviation = " << m_metrics.AverageAbsoluteDeviation << endl;
    cout << "Curvature Heterogeneity: " << m_metrics.CurvatureHeterogeneity << endl;
    cout << "P: " << m_metrics.P << endl;
}

double SegmentationMetrics::background_average(const pcl::PointCloud<pcl::Normal>::ConstPtr &normal_cloud, int num_p)
{
    // computes the average feature value for the background
    // FIXME: What is background?
    // feature value: curvature
    double sum = 0.0;
    for(size_t i = 0; i < normal_cloud->points.size(); ++i)
    {
        sum += normal_cloud->points[i].curvature;
    }
    return sum / num_p; // return average
}

double SegmentationMetrics::region_average(pcl::PointCloud<pcl::Normal>::Ptr &cloudn, int num_p)
{
    //computes the average feature value for the region
    // feature value: curvature

    double sum = 0.0;
    double average;
    for(size_t i = 0; i < cloudn->points.size(); ++i)
    {
        sum += cloudn->points[i].curvature;
    }
    average = sum / num_p;
    return average;
}

double SegmentationMetrics::compute_heterogeneity(double b_average, double r_average)
{
    double contrast;
    contrast = (abs(b_average - r_average) / (b_average + r_average));
    return contrast;
}

// --------------------------------------------
// performance evaluation curvature
// --------------------------------------------

double SegmentationMetrics::min(pcl::PointCloud<pcl::Normal>::Ptr &merged, int num_p)
{
    double minimum = merged->points[0].curvature;
    for (int i = 0; i < num_p; ++i)
    {
        if (minimum > merged->points[i].curvature)
        {
            minimum = merged->points[i].curvature;
        }
    }
    return minimum;
}

double SegmentationMetrics::max(pcl::PointCloud<pcl::Normal>::Ptr &merged, int num_p)
{
    double maximum = merged->points[0].curvature;
    for (int i = 0; i < num_p; ++i)
    {
        if (maximum < merged->points[i].curvature)
        {
            maximum = merged->points[i].curvature;
        }
    }
    return maximum;
}

double SegmentationMetrics::compute_average(int num_p, pcl::PointCloud<pcl::Normal>::Ptr &cloud)
{
    double sum = 0.0;
    double average = 0.0;
    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
        sum += cloud->points[i].curvature;
    }
    average = sum / num_p;
    return average;
}

double SegmentationMetrics::compute_v(double mean, pcl::PointCloud<pcl::Normal>::Ptr &cloud)
{
    double sum = 0.0;
    double variance = 0.0;

    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        sum += ((mean - cloud->points[i].curvature) * (mean - cloud->points[i].curvature));

    }
    variance = sum / cloud->points.size();
    return variance;
}

// --------------------------------------------
// performance evaluation rgb
// --------------------------------------------

double SegmentationMetrics::min_rgb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &merged, int num_p)
{
    double minimum = merged->points[0].rgb;
    for (int i = 0; i < num_p; ++i)
    {
        if (minimum > merged->points[i].rgb)
        {
            minimum = merged->points[i].rgb;
        }
    }
    return minimum;
}

double SegmentationMetrics::max_rgb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &merged, int num_p)
{
    double maximum = merged->points[0].rgb;
    for (int i = 0; i < num_p; ++i)
    {
        if (maximum < merged->points[i].rgb)
        {
            maximum = merged->points[i].rgb;
        }
    }
    return maximum;
}

double SegmentationMetrics::compute_average_rgb(int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    double sum = 0.0;
    double average = 0.0;
    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
        sum += cloud->points[i].rgb;
    }
    average = sum / num_p;
    return average;
}

double SegmentationMetrics::compute_v_rgb(double mean, int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    double sum = 0.0;
    double variance = 0.0;

    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
        sum += ((mean - cloud->points[i].rgb) * (mean - cloud->points[i].rgb));
    }
    variance = sum / num_p;
    return variance;
}

// --------------------------------------------
// average absolute deviation
// --------------------------------------------

double SegmentationMetrics::compute_abs(double mean,int num_p, pcl::PointCloud<pcl::Normal>::Ptr &cloud)
{
    double sum = 0.0;
    double variance = 0.0;

    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
        sum += (abs(mean - cloud->points[i].curvature));
    }
    variance = sum / num_p;
    return variance;
}

// --------------------------------------------
// computes average absolute deviation
// --------------------------------------------

double SegmentationMetrics::compute_absrgb(double mean, int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    double sum = 0.0;
    double variance = 0.0;

    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
        sum += (abs(mean - cloud->points[i].rgb));
    }
    variance = sum / num_p;
    return variance;
}


// --------------------------------------------
// colour heterogeneity
// --------------------------------------------

double SegmentationMetrics::background_averagergb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloudrgb, int num_p)
{
    //computes the average feature value for the background
    // feature value: curvature

    double sum = 0.0;
    double average;
    for(size_t i = 0; i < cloudrgb->points.size(); ++i)
    {
        sum += cloudrgb->points[i].rgb;
    }
    average = sum / num_p;
    return average;
}

double SegmentationMetrics::region_averagergb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloudrgb, int num_p)
{
    //computes the average feature value for the region
    // feature value: curvature

    double sum = 0.0;
    double average;
    for(size_t i = 0; i < cloudrgb->points.size(); ++i)
    {
        sum += cloudrgb->points[i].rgb;
    }
    average = sum / num_p;
    return average;
}

double SegmentationMetrics::compute_heterogeneityrgb(double b_averagergb, double r_averagergb)
{
    double contrast;
    contrast = (abs(b_averagergb - r_averagergb) / (b_averagergb + r_averagergb));
    return contrast;
}


} // namespace
