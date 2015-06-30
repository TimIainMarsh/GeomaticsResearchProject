#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T10:24:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Test1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

# includes
INCLUDEPATH += "/usr/include/eigen3/" \
"/usr/include/pcl-1.4/" \
"/usr/include/vtk-5.6/" \
"/usr/include/boost/" \
"/usr/include/flann/" \
"/usr/include/openni/" \

# libs
LIBS += -lQtGui -lQtCore -lQtOpenGL \
        -lpcl_registration -lpcl_sample_consensus -lpcl_features -lpcl_filters -lpcl_surface -lpcl_segmentation \
        -lpcl_search -lpcl_range_image -lpcl_kdtree -lpcl_octree -lflann_cpp -lpcl_common -lpcl_io \
        -lpcl_visualization \
        -L/usr/lib -lvtkCommon -lvtksys -lQVTK -lvtkQtChart -lvtkViews -lvtkWidgets -lvtkRendering -lvtkGraphics -lvtkImaging -lvtkIO -lvtkFiltering -lvtkDICOMParser -lvtkmetaio -lvtkexoIIc -lvtkftgl -lvtkHybrid \
 -L/usr/lib -lboost_thread \
