#include "segmentor.h"

namespace P {


Segmentor::Segmentor()
{

}

Segmentor::~Segmentor()
{

}

void Segmentor::setParameters(const int& knn,
                              const float& smoothness_threshold, const float& curvature_threshold,
                              const int& min_cluster_size, const int& max_cluster_size)
{
    m_knn = knn;
    m_smoothness_threshold = smoothness_threshold;
    m_curvature_threshold = curvature_threshold;

    m_min_cluster = min_cluster_size;
    m_max_cluster = max_cluster_size;
}

} // namespace
