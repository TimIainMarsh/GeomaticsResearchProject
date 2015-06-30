#ifndef SEGMENTATIONMETRICS_H
#define SEGMENTATIONMETRICS_H

// C/C++ Libraries
#include <iostream>

// PCL Libraries
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/segmentation/region_growing.h>


namespace P {


class SegmentationMetrics
{
public:
    SegmentationMetrics();
    ~SegmentationMetrics();

    // type definitions
    typedef pcl::PointCloud<pcl::PointXYZRGBA> ColorACloud;
    typedef pcl::PointCloud<pcl::PointXYZRGB> ColorCloud;
    typedef pcl::PointCloud<pcl::PointXYZI> GrayCloud;
    typedef pcl::PointCloud<pcl::PointXYZ> MonochromeCloud;

    typedef pcl::PointCloud <pcl::Normal> NormalCloud;
    typedef pcl::search::Search<pcl::PointXYZRGB> SearchXYZRGB;
    typedef vector<pcl::PointIndices> vecPointIndeces;


    template <class Cloud, class PointType, class Indeces>
    void get(Cloud &cloud, NormalCloud::Ptr &normalcloud, Indeces &clusters)
    {
        // --------------------------------------------
        // prepare the metrics
        metricsPreProcess<const ColorCloud::ConstPtr &>(cloud, normalcloud);

        // declare file writers
        pcl::PCDWriter writer;

        cout << "Writing " << clusters.size() << " segments to separate files ..." << clusters.size() << endl;
        int segindex = 0;
        for (std::vector<pcl::PointIndices>::const_iterator it = clusters.begin (); it != clusters.end (); ++it)
        {
            pcl::PointCloud<pcl::Normal>::Ptr normal_cloud_seg (new pcl::PointCloud<pcl::Normal>);
            pcl::PointCloud<PointType>::Ptr point_cloud_seg (new pcl::PointCloud<PointType>);
            //        pcl::PointCloud<MyPointType>::Ptr first_seg (new pcl::PointCloud<MyPointType>);

            for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
            {
                normal_cloud_seg->points.push_back (normalcloud->points[*pit]);
                point_cloud_seg->points.push_back (cloud->points[*pit]);
            }

            // setup the normal cloud
            normal_cloud_seg->width = normal_cloud_seg->points.size ();
            normal_cloud_seg->height = 1;
            normal_cloud_seg->is_dense = true;

            // setup the point cloud
            point_cloud_seg->width = point_cloud_seg->points.size ();
            point_cloud_seg->height = 1;
            point_cloud_seg->is_dense = true;

            stringstream filename_normal;
            filename_normal << "normals/segment_" << segindex << ".pcd";
            writer.write<pcl::Normal> (filename_normal.str(), *normal_cloud_seg, false);

            stringstream filename_cloud;
            filename_cloud << "segments/segment_" << segindex << ".pcd";
            writer.write<PointType> (filename_cloud.str(), *point_cloud_seg, false);

            ++segindex;
        }

        // --------------------------------------------
        // get curvature metrics
        getCurvatureMetrics(normalcloud);
    }

protected:
    double background_average(const pcl::PointCloud<pcl::Normal>::ConstPtr &cloud, int num_p);

    double region_average(pcl::PointCloud<pcl::Normal>::Ptr &cloudn, int num_p);

    double compute_heterogeneity(double b_average, double r_average);

    double min(pcl::PointCloud<pcl::Normal>::Ptr &merged, int num_p);

    double max(pcl::PointCloud<pcl::Normal>::Ptr &merged, int num_p);

    double compute_average(int num_p, pcl::PointCloud<pcl::Normal>::Ptr &cloud);

    double compute_v(double mean, pcl::PointCloud<pcl::Normal>::Ptr &cloud);

    double min_rgb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &merged, int num_p);

    double max_rgb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &merged, int num_p);

    double compute_average_rgb(int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud);

    double compute_v_rgb(double mean, int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud);

    double compute_abs(double mean,int num_p, pcl::PointCloud<pcl::Normal>::Ptr &cloud);

    double compute_absrgb(double mean, int num_p, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud);

    double background_averagergb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloudrgb, int num_p);

    double region_averagergb(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &cloudrgb, int num_p);

    double compute_heterogeneityrgb(double b_averagergb, double r_averagergb);

    // preprocessing for metrics
    template <class Cloud>
    void metricsPreProcess(Cloud& cloud, NormalCloud::Ptr& normalcloud)
    {
        // normalised segmentation standard deviation
        // FIXME: check this
        // feature value average for the whole point cloud
        feature_average = background_average(normalcloud, normalcloud->points.size());
        Max_f = max(normalcloud, normalcloud->points.size());
        Min_f = min(normalcloud, normalcloud->points.size());
        df = Max_f - Min_f;
        N = (point_num * df * df) / 2.0;
        N_abs = (point_num* fabs(df));

        Max_frgb = max_rgb(cloud, cloud->points.size());
        Min_frgb = min_rgb(cloud, cloud->points.size());
        dfrgb = Max_frgb - Min_frgb;
        Nrgb = (point_num * (dfrgb * dfrgb)) / 2.0;
        N_devrgb = (point_num * (fabs(dfrgb)));
    }

    // get curvature metrics
    void getCurvatureMetrics(NormalCloud::Ptr &normalcloud);

    // --------------------------------------------
    // get colour metrics
    template <class Cloud, class PointType>
    void getColourMetrics(Cloud cloud, NormalCloud::Ptr &normalcloud)
    {
        double sum = 0.0;
        double dev_sumrgb = 0.0;
        for(int segindex = 0; segindex < segcount; ++segindex)
        {
            stringstream filename_cloud;

            filename_cloud << "segments/segment_" << segindex << ".pcd";
            //std::cout<<"points on segment_"<<num_seg<<std::endl;

            pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudrgb (new pcl::PointCloud<pcl::PointXYZRGB>);
            if (pcl::io::loadPCDFile<PointType> (filename_cloud.str(), *cloudrgb) == -1)
            {
                PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
            }
            else
            {
                double mean_frgb = compute_average_rgb(cloudrgb->points.size(), cloudrgb);
                double variance = compute_v_rgb(mean_frgb, cloudrgb->points.size(), cloudrgb);
                double abs_devrgb = compute_absrgb(mean_frgb, cloudrgb->points.size(), cloudrgb);

                double max_vrgb = (dfrgb * dfrgb) / 2.0;
                sum += (cloudrgb->points.size() * (variance) / Nrgb);
                dev_sumrgb += (cloudrgb->points.size() * abs_devrgb / N_devrgb);
            }
        }

        m_metrics.RGBIntraRegionUniformity = 1 - sum;
        m_metrics.RGBAverageAbsoluteDeviation = 1 - dev_sumrgb;

        cout << "--------------------------------------------" << endl;
        cout << "Colour Metrics" << endl;
        cout<< "rgb: intra-Region Uniformity = " << m_metrics.RGBIntraRegionUniformity << endl;
        cout<< "rgb: average absolute deviation = " << m_metrics.RGBAverageAbsoluteDeviation << endl;


        double b_average = background_average(normalcloud, normalcloud->points.size());
        double b_averagergb = background_averagergb(cloud, cloud->points.size());

        double sum2 = 0.0;
        double sum1 = 0.0;

        for(int segindex = 0; segindex < segcount; ++segindex)
        {
            stringstream filename_normals;
            stringstream filename_cloud;

            filename_normals << "normals/segment_" << segindex << ".pcd";
            filename_cloud << "segments/segment_" << segindex << ".pcd";

            // curvature point cloud
            pcl::PointCloud<pcl::Normal>::Ptr cloudc (new pcl::PointCloud<pcl::Normal>);
            if ( pcl::io::loadPCDFile <pcl::Normal> (filename_normals.str(), *cloudc) == -1)
            {
                std::cout << "Cloud reading failed." << std::endl;
            }
            else
            {
                //rgb_point cloud
                pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudrgb (new pcl::PointCloud<pcl::PointXYZRGB>);
                if (pcl::io::loadPCDFile <pcl::PointXYZRGB> (filename_cloud.str(), *cloudrgb) == -1)
                {
                    std::cout << "Cloud reading failed." << std::endl;
                }
                else
                {
                    double r_average = region_average(cloudc,cloudc->points.size());
                    double rgb_average = region_averagergb(cloudrgb, cloudrgb->points.size());

                    double heterogeneity = compute_heterogeneity(b_average, r_average);
                    double rgb_heterogeneity = compute_heterogeneityrgb(b_averagergb, rgb_average);

                    //std::cout<<"heterogeneity: "<<heterogeneity<<" "<<"rgb heterogeneity: "<<rgb_heterogeneity<<std::endl;

                    sum2 += heterogeneity;
                    sum1 += rgb_heterogeneity;

                    /*std::ofstream outfile;

               outfile.open("test.txt", std::ios_base::app);
               outfile << heterogeneity; */
                }
            }
        }

        m_metrics.RGBHeterogeneity = sum1 / segcount;

        cout << "RGB Heterogeneity: " << m_metrics.RGBHeterogeneity << endl;
    }

private:
    // segmentation metrics
    double sum; // see getCurvatureHomogeneityMeasure
    double seg_stddev; // see getCurvatureHomogeneityMeasure
    double NPSS;
    double IntraRegionUniformity;
    double AverageAbsoluteDeviation;
    double CurvatureHeterogeneity;
    double P;
    double RGBHeterogeneity;
    double RGBIntraRegionUniformity;
    double RGBAverageAbsoluteDeviation;

    // metrics variables
    int segcount;
    int point_num;

    double feature_average;
    double Max_f;
    double Min_f;
    double df;
    double N;
    double N_abs;

    double Max_frgb;
    double Min_frgb;
    double dfrgb;
    double Nrgb;
    double N_devrgb;
};


} // namespace

#endif // SEGMENTATIONMETRICS_H
