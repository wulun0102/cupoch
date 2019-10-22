#pragma once

#include <Eigen/Core>
#include <memory>
#include <thrust/device_vector.h>

#include "cupoc/geometry/kdtree_search_param.h"
#include "cupoc/geometry/pointcloud.h"
#include "cupoc/utility/eigen.h"

namespace flann {
template <typename T>
class Matrix;
template <typename T>
struct L2;
template <typename T>
class Index;
}  // namespace flann

namespace cupoc {
namespace geometry {

class KDTreeFlann {
public:
    KDTreeFlann();
    KDTreeFlann(const Eigen::MatrixXf &data);
    KDTreeFlann(const PointCloud &data);
    ~KDTreeFlann();
    KDTreeFlann(const KDTreeFlann &) = delete;
    KDTreeFlann &operator=(const KDTreeFlann &) = delete;

public:
    bool SetMatrixData(const Eigen::MatrixXf_u &data);
    bool SetGeometry(const PointCloud &geometry);

    template <typename T>
    int Search(const T &query,
               const KDTreeSearchParam &param,
               thrust::device_vector<int> &indices,
               thrust::device_vector<float> &distance2) const;

    template <typename T>
    int SearchKNN(const T &query,
                  int knn,
                  thrust::device_vector<int> &indices,
                  thrust::device_vector<float> &distance2) const;

    template <typename T>
    int SearchRadius(const T &query,
                     float radius,
                     thrust::device_vector<int> &indices,
                     thrust::device_vector<float> &distance2) const;

    template <typename T>
    int SearchHybrid(const T &query,
                     float radius,
                     int max_nn,
                     thrust::device_vector<int> &indices,
                     thrust::device_vector<float> &distance2) const;

private:
    bool SetRawData(const Eigen::Map<const Eigen::MatrixXf_u> &data);

protected:
    thrust::device_vector<float> data_;
    std::unique_ptr<flann::Matrix<float>> flann_dataset_;
    std::unique_ptr<flann::Index<flann::L2<float>>> flann_index_;
    size_t dimension_ = 0;
    size_t dataset_size_ = 0;
};

}  // namespace geometry
}  // namespace cupoc