#include "cupoch/geometry/boundingvolume.h"

#include "cupoch_pybind/docstring.h"
#include "cupoch_pybind/geometry/geometry.h"
#include "cupoch_pybind/geometry/geometry_trampoline.h"

using namespace cupoch;

void pybind_boundingvolume(py::module &m) {
    py::class_<geometry::OrientedBoundingBox,
               PyGeometry3D<geometry::OrientedBoundingBox>,
               std::shared_ptr<geometry::OrientedBoundingBox>,
               geometry::GeometryBase<3>>
            oriented_bounding_box(m, "OrientedBoundingBox",
                                  "Class that defines an oriented box that can "
                                  "be computed from 3D geometries.");
    py::detail::bind_default_constructor<geometry::OrientedBoundingBox>(
            oriented_bounding_box);
    py::detail::bind_copy_functions<geometry::OrientedBoundingBox>(
            oriented_bounding_box);
    oriented_bounding_box
            .def(py::init<const Eigen::Vector3f &, const Eigen::Matrix3f &,
                          const Eigen::Vector3f &>(),
                 "Create OrientedBoudingBox from center, rotation R and extent "
                 "in x, y and z "
                 "direction",
                 "center"_a, "R"_a, "extent"_a)
            .def("__repr__",
                 [](const geometry::OrientedBoundingBox &box) {
                     return std::string("geometry::OrientedBoundingBox");
                 })
            .def("get_point_indices_within_bounding_box",
                 &geometry::OrientedBoundingBox::
                         GetPointIndicesWithinBoundingBox,
                 "Return indices to points that are within the bounding box.",
                 "points"_a)
            .def_static("create_from_axis_aligned_bounding_box",
                        &geometry::OrientedBoundingBox::
                                CreateFromAxisAlignedBoundingBox,
                        "Returns an oriented bounding box from the "
                        "AxisAlignedBoundingBox.",
                        "aabox"_a)
            .def("volume", &geometry::OrientedBoundingBox::Volume,
                 "Returns the volume of the bounding box.")
            .def("get_box_points", &geometry::OrientedBoundingBox::GetBoxPoints,
                 "Returns the eight points that define the bounding box.")
            .def_readwrite("center", &geometry::OrientedBoundingBox::center_,
                           "``float32`` array of shape ``(3, )``")
            .def_readwrite("R", &geometry::OrientedBoundingBox::R_,
                           "``float32`` array of shape ``(3,3 )``")
            .def_readwrite("extent", &geometry::OrientedBoundingBox::extent_,
                           "``float32`` array of shape ``(3, )``")
            .def_readwrite("color", &geometry::OrientedBoundingBox::color_,
                           "``float32`` array of shape ``(3, )``");
    docstring::ClassMethodDocInject(m, "OrientedBoundingBox", "volume");
    docstring::ClassMethodDocInject(m, "OrientedBoundingBox", "get_box_points");
    docstring::ClassMethodDocInject(m, "OrientedBoundingBox",
                                    "get_point_indices_within_bounding_box",
                                    {{"points", "A list of points."}});
    docstring::ClassMethodDocInject(
            m, "OrientedBoundingBox", "create_from_axis_aligned_bounding_box",
            {{"aabox",
              "AxisAlignedBoundingBox object from which OrientedBoundingBox is "
              "created."}});

    py::class_<geometry::AxisAlignedBoundingBox,
               PyGeometry3D<geometry::AxisAlignedBoundingBox>,
               std::shared_ptr<geometry::AxisAlignedBoundingBox>,
               geometry::GeometryBase<3>>
            axis_aligned_bounding_box(m, "AxisAlignedBoundingBox",
                                      "Class that defines an axis_aligned box "
                                      "that can be computed from 3D "
                                      "geometries, The axis aligned bounding "
                                      "box uses the cooridnate axes for "
                                      "bounding box generation.");
    py::detail::bind_default_constructor<geometry::AxisAlignedBoundingBox>(
            axis_aligned_bounding_box);
    py::detail::bind_copy_functions<geometry::AxisAlignedBoundingBox>(
            axis_aligned_bounding_box);
    axis_aligned_bounding_box
            .def(py::init<const Eigen::Vector3f &, const Eigen::Vector3f &>(),
                 "Create an AxisAlignedBoundingBox from min bounds and max "
                 "bounds in x, y and z",
                 "min_bound"_a, "max_bound"_a)
            .def("__repr__",
                 [](const geometry::AxisAlignedBoundingBox &box) {
                     return std::string("geometry::AxisAlignedBoundingBox");
                 })
            .def("volume", &geometry::AxisAlignedBoundingBox::Volume,
                 "Returns the volume of the bounding box.")
            .def("get_box_points",
                 &geometry::AxisAlignedBoundingBox::GetBoxPoints,
                 "Returns the eight points that define the bounding box.")
            .def("get_extent", &geometry::AxisAlignedBoundingBox::GetExtent,
                 "Get the extent/length of the bounding box in x, y, and z "
                 "dimension.")
            .def("get_half_extent",
                 &geometry::AxisAlignedBoundingBox::GetHalfExtent,
                 "Returns the half extent of the bounding box.")
            .def("get_max_extent",
                 &geometry::AxisAlignedBoundingBox::GetMaxExtent,
                 "Returns the maximum extent, i.e. the maximum of X, Y and Z "
                 "axis")
            .def("get_point_indices_within_bounding_box",
                 &geometry::AxisAlignedBoundingBox::
                         GetPointIndicesWithinBoundingBox,
                 "Return indices to points that are within the bounding box.",
                 "points"_a)
            .def("get_print_info",
                 &geometry::AxisAlignedBoundingBox::GetPrintInfo,
                 "Returns the 3D dimensions of the bounding box in string "
                 "format.")
            .def_static(
                    "create_from_points",
                    py::overload_cast<const utility::device_vector<Eigen::Vector3f>&>(&geometry::AxisAlignedBoundingBox::CreateFromPoints),
                    "Creates the bounding box that encloses the set of points.",
                    "points"_a)
            .def_readwrite("min_bound",
                           &geometry::AxisAlignedBoundingBox::min_bound_,
                           "``float32`` array of shape ``(3, )``")
            .def_readwrite("max_bound",
                           &geometry::AxisAlignedBoundingBox::max_bound_,
                           "``float32`` array of shape ``(3, )``")
            .def_readwrite("color", &geometry::AxisAlignedBoundingBox::color_,
                           "``float32`` array of shape ``(3, )``");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox", "volume");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "get_box_points");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox", "get_extent");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "get_half_extent");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "get_max_extent");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "get_point_indices_within_bounding_box",
                                    {{"points", "A list of points."}});
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "get_print_info");
    docstring::ClassMethodDocInject(m, "AxisAlignedBoundingBox",
                                    "create_from_points",
                                    {{"points", "A list of points."}});
}