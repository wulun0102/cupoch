#include "cupoc_pybind/geometry/geometry.h"
#include "cupoc/geometry/kdtree_flann.h"

using namespace cupoc;

void pybind_kdtreeflann(py::module &m) {
    // cupoc.geometry.KDTreeSearchParam
    py::class_<geometry::KDTreeSearchParam> kdtreesearchparam(
            m, "KDTreeSearchParam", "Base class for KDTree search parameters.");
    kdtreesearchparam.def("get_search_type",
                          &geometry::KDTreeSearchParam::GetSearchType,
                          "Get the search type (KNN, Radius, Hybrid) for the "
                          "search parameter.");

    // cupoc.geometry.KDTreeSearchParam.Type
    py::enum_<geometry::KDTreeSearchParam::SearchType> kdtree_search_param_type(
            kdtreesearchparam, "Type", py::arithmetic());
    kdtree_search_param_type
            .value("KNNSearch", geometry::KDTreeSearchParam::SearchType::Knn)
            .value("RadiusSearch",
                   geometry::KDTreeSearchParam::SearchType::Radius)
            .value("HybridSearch",
                   geometry::KDTreeSearchParam::SearchType::Hybrid)
            .export_values();

    // cupoc.geometry.KDTreeSearchParamKNN
    py::class_<geometry::KDTreeSearchParamKNN> kdtreesearchparam_knn(
            m, "KDTreeSearchParamKNN", kdtreesearchparam,
            "KDTree search parameters for pure KNN search.");
    kdtreesearchparam_knn.def(py::init<int>(), "knn"_a = 30)
            .def("__repr__",
                 [](const geometry::KDTreeSearchParamKNN &param) {
                     return std::string(
                                    "geometry::KDTreeSearchParamKNN with knn "
                                    "= ") +
                            std::to_string(param.knn_);
                 })
            .def_readwrite("knn", &geometry::KDTreeSearchParamKNN::knn_,
                           "``knn`` neighbors will be searched.");

    // cupoc.geometry.KDTreeSearchParamRadius
    py::class_<geometry::KDTreeSearchParamRadius> kdtreesearchparam_radius(
            m, "KDTreeSearchParamRadius", kdtreesearchparam,
            "KDTree search parameters for pure radius search.");
    kdtreesearchparam_radius.def(py::init<float>(), "radius"_a)
            .def("__repr__",
                 [](const geometry::KDTreeSearchParamRadius &param) {
                     return std::string(
                                    "geometry::KDTreeSearchParamRadius with "
                                    "radius = ") +
                            std::to_string(param.radius_);
                 })
            .def_readwrite("radius",
                           &geometry::KDTreeSearchParamRadius::radius_,
                           "Search radius.");

    // cupoc.geometry.KDTreeSearchParamHybrid
    py::class_<geometry::KDTreeSearchParamHybrid> kdtreesearchparam_hybrid(
            m, "KDTreeSearchParamHybrid", kdtreesearchparam,
            "KDTree search parameters for hybrid KNN and radius search.");
    kdtreesearchparam_hybrid
            .def(py::init<float, int>(), "radius"_a, "max_nn"_a)
            .def("__repr__",
                 [](const geometry::KDTreeSearchParamHybrid &param) {
                     return std::string(
                                    "geometry::KDTreeSearchParamHybrid with "
                                    "radius = ") +
                            std::to_string(param.radius_) +
                            " and max_nn = " + std::to_string(param.max_nn_);
                 })
            .def_readwrite("radius",
                           &geometry::KDTreeSearchParamHybrid::radius_,
                           "Search radius.")
            .def_readwrite(
                    "max_nn", &geometry::KDTreeSearchParamHybrid::max_nn_,
                    "At maximum, ``max_nn`` neighbors will be searched.");
}