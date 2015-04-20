#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T23:13:37
#
#-------------------------------------------------

QT       += core opengl xml

QT       -= gui

TARGET = OpenCV_PCL
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp



#-------------------------------------------------
#
# OpenCV Includes
#
#-------------------------------------------------
win32 \
{
    OPENCV_PATH = "C:/downloads/OpenCV/opencv-2.4.11/opencv/build"
    message("OPENCV_PATH:   " $${OPENCV_PATH})

    CONFIG(release, debug|release) \
    {
        LIBS += -L$${OPENCV_PATH}/x86/vc10/lib/ \
            -lopencv_calib3d2411\
            -lopencv_contrib2411\
            -lopencv_core2411\
            -lopencv_features2d2411\
            -lopencv_flann2411\
            -lopencv_gpu2411\
            -lopencv_highgui2411\
            -lopencv_imgproc2411\
            -lopencv_legacy2411\
            -lopencv_ml2411\
            -lopencv_nonfree2411\
            -lopencv_objdetect2411\
            -lopencv_ocl2411\
            -lopencv_photo2411\
            -lopencv_stitching2411\
            -lopencv_superres2411\
            -lopencv_ts2411\
            -lopencv_video2411\
            -lopencv_videostab2411
    }
    else \
    {
        LIBS += -L$${OPENCV_PATH}/x86/vc10/lib/ \
            -lopencv_calib3d2411d\
            -lopencv_contrib2411d\
            -lopencv_core2411d\
            -lopencv_features2d2411d\
            -lopencv_flann2411d\
            -lopencv_gpu2411d\
            -lopencv_highgui2411d\
            -lopencv_imgproc2411d\
            -lopencv_legacy2411d\
            -lopencv_ml2411d\
            -lopencv_nonfree2411d\
            -lopencv_objdetect2411d\
            -lopencv_ocl2411d\
            -lopencv_photo2411d\
            -lopencv_stitching2411d\
            -lopencv_superres2411d\
            -lopencv_ts2411d\
            -lopencv_video2411d\
            -lopencv_videostab2411d
    }

    INCLUDEPATH += $${OPENCV_PATH}/include
    DEPENDPATH  += $${OPENCV_PATH}/include
}

#-------------------------------------------------
#
# Point Cloud Library Includes
#
#-------------------------------------------------
win32 \
{
    PCL_PATH = "C:/Program Files (x86)/PCL 1.6.0"

    message("PCL PATH:   " $${PCL_PATH})

    CONFIG(release, debug|release) \
    {
        LIBS += -ladvapi32 #-lwbemuuid

#        LIBS += "-LC:/Program Files (x86)/PCL 1.6.0/lib/" \
        LIBS += -L$${PCL_PATH}/lib/ \
            -lpcl_apps_release \
            -lpcl_common_release \
            -lpcl_features_release \
            -lpcl_filters_release \
            -lpcl_io_release \
            -lpcl_io_ply_release \
            -lpcl_kdtree_release \
            -lpcl_keypoints_release \
            -lpcl_octree_release \
            -lpcl_registration_release \
            -lpcl_sample_consensus_release \
            -lpcl_search_release \
            -lpcl_segmentation_release \
            -lpcl_surface_release \
            -lpcl_tracking_release \
            -lpcl_visualization_release

        LIBS += -L$${PCL_PATH}/3rdParty/Boost/lib/ \
            -lboost_graph-vc100-mt-1_49 \
            -lboost_system-vc100-mt-1_49 \
            -lboost_filesystem-vc100-mt-1_49 \
            -lboost_thread-vc100-mt-1_49 \
            -lboost_date_time-vc100-mt-1_49 \
            -lboost_iostreams-vc100-mt-1_49
#            -lboost_graph_parallel-vc100-mt-1_49 \
#            -lboost_math_c99-vc100-mt-1_49 \
#            -lboost_math_c99f-vc100-mt-1_49 \
#            -lboost_math_tr1-vc100-mt-1_49 \
#            -lboost_math_tr1f-vc100-mt-1_49 \
#            -lboost_mpi-vc100-mt-1_49 \
#            -lboost_prg_exec_monitor-vc100-mt-1_49 \
#            -lboost_program_options-vc100-mt-1_49 \
#            -lboost_random-vc100-mt-1_49 \
#            -lboost_thread-vc100-mt-1_49

        LIBS += -L$${PCL_PATH}/3rdParty/FLANN/lib/ \
            -lflann

        LIBS += -L$${PCL_PATH}/3rdParty/Qhull/lib/ \
            -lqhull6

        LIBS += -L$${PCL_PATH}/3rdParty/VTK/lib/vtk-5.8/ \
#            -lMapReduceMPI \
#            -lmpistubs \
#            -lQVTK \
#            -lvtkalglib \
#            -lvtkCharts \
            -lvtkCommon \
            -lvtkDICOMParser \
            -lvtkexoIIc \
            -lvtkexpat \
            -lvtkFiltering \
            -lvtkfreetype \
            -lvtkftgl \
#            -lvtkGenericFiltering \
#            -lvtkGeovis \
            -lvtkGraphics \
#            -lvtkhdf5 \
            -lvtkHybrid \
            -lvtkImaging \
#            -lvtkInfovis \
            -lvtkIO \
            -lvtkjpeg \
#            -lvtklibxml2 \
            -lvtkmetaio \
#            -lvtkNetCDF_cxx \
            -lvtkNetCDF \
            -lvtkpng \
#            -lvtkproj4 \
            -lvtkRendering \
            -lvtksqlite \
            -lvtksys \
            -lvtktiff \
            -lvtkverdict \
#            -lvtkViews \
#            -lvtkVolumeRendering \
#            -lvtkWidgets \
            -lvtkzlib
    }
    else \
    {
        LIBS += -ladvapi32 #-lwbemuuid

        LIBS += -L$${PCL_PATH}/lib/ \
            -lpcl_apps_debug \
            -lpcl_common_debug \
            -lpcl_features_debug \
            -lpcl_filters_debug \
            -lpcl_io_debug \
            -lpcl_io_ply_debug \
            -lpcl_kdtree_debug \
            -lpcl_keypoints_debug \
            -lpcl_octree_debug \
            -lpcl_registration_debug \
            -lpcl_sample_consensus_debug \
            -lpcl_search_debug \
            -lpcl_segmentation_debug \
            -lpcl_surface_debug \
            -lpcl_tracking_debug \
            -lpcl_visualization_debug

        LIBS += -L$${PCL_PATH}/3rdParty/Boost/lib/ \
            -lboost_graph-vc100-mt-gd-1_49 \
            -lboost_system-vc100-mt-gd-1_49 \
            -lboost_filesystem-vc100-mt-gd-1_49 \
            -lboost_thread-vc100-mt-gd-1_49 \
            -lboost_date_time-vc100-mt-gd-1_49 \
            -lboost_iostreams-vc100-mt-gd-1_49
#            -lboost_graph_parallel-vc100-mt-gd-1_49 \
#            -lboost_math_c99-vc100-mt-gd-1_49 \
#            -lboost_math_c99f-vc100-mt-gd-1_49 \
#            -lboost_math_tr1-vc100-mt-gd-1_49 \
#            -lboost_math_tr1f-vc100-mt-gd-1_49 \
#            -lboost_mpi-vc100-mt-gd-1_49 \
#            -lboost_prg_exec_monitor-vc100-mt-gd-1_49 \
#            -lboost_program_options-vc100-mt-gd-1_49 \
#            -lboost_random-vc100-mt-gd-1_49 \
#            -lboost_thread-vc100-mt-gd-1_49

        LIBS += -L$${PCL_PATH}/3rdParty/FLANN/lib/ \
            -lflann-gd

        LIBS += -L$${PCL_PATH}/3rdParty/Qhull/lib/ \
            -lqhull6_d

        LIBS += -L$${PCL_PATH}/3rdParty/VTK/lib/vtk-5.8/ \
#            -lMapReduceMPI-gd \
#            -lmpistubs-gd \
#            -lQVTK-gd \
#            -lvtkalglib-gd \
#            -lvtkCharts-gd \
            -lvtkCommon-gd \
            -lvtkDICOMParser-gd \
            -lvtkexoIIc-gd \
            -lvtkexpat-gd \
            -lvtkFiltering-gd \
            -lvtkfreetype-gd \
            -lvtkftgl-gd \
#            -lvtkGenericFiltering-gd \
#            -lvtkGeovis-gd \
            -lvtkGraphics-gd \
#            -lvtkhdf5-gd \
            -lvtkHybrid-gd \
            -lvtkImaging-gd \
#            -lvtkInfovis-gd \
            -lvtkIO-gd \
            -lvtkjpeg-gd \
#            -lvtklibxml2-gd \
            -lvtkmetaio-gd \
#            -lvtkNetCDF_cxx-gd \
            -lvtkNetCDF-gd \
            -lvtkpng-gd \
#            -lvtkproj4-gd \
            -lvtkRendering-gd \
            -lvtksqlite-gd \
            -lvtksys-gd \
            -lvtktiff-gd \
            -lvtkverdict-gd \
#            -lvtkViews-gd \
#            -lvtkVolumeRendering-gd \
#            -lvtkWidgets-gd \
            -lvtkzlib-gd
    }

    INCLUDEPATH += $${PCL_PATH}/include/pcl-1.6
    DEPENDPATH  += $${PCL_PATH}/include/pcl-1.6

    INCLUDEPATH += $${PCL_PATH}/3rdParty/Boost/include
    DEPENDPATH  += $${PCL_PATH}/3rdParty/Boost/include

    INCLUDEPATH += $${PCL_PATH}/3rdParty/Eigen/include
    DEPENDPATH  += $${PCL_PATH}/3rdParty/Eigen/include

    INCLUDEPATH += $${PCL_PATH}/3rdParty/FLANN/include
    DEPENDPATH  += $${PCL_PATH}/3rdParty/FLANN/include

    INCLUDEPATH += $${PCL_PATH}/3rdParty/VTK/include/vtk-5.8
    DEPENDPATH  += $${PCL_PATH}/3rdParty/VTK/include/vtk-5.8
}




