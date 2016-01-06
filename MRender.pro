#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T18:53:44
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MRender
TEMPLATE = app


SOURCES += GUI/main.cpp\
    GUI/mainwindow.cpp \
    Render/render.cpp \
    Objects/camera.cpp \
    Objects/object3d.cpp \
    Objects/light.cpp \
    Objects/sphere.cpp \
    Objects/plane.cpp \
    Objects/box.cpp \
    Objects/cylinder.cpp \
    Render/material.cpp \
    Render/color.cpp \
    Render/ray.cpp \
    Render/scene.cpp \
    Render/canvas.cpp \
    Math/vec4.cpp \
    Math/mtx4.cpp \
    GUI/imagecreator.cpp \
    GUI/filemanager.cpp \
    Objects/boundingbox.cpp \
    Render/texture.cpp \
    Objects/pontuallight.cpp \
    Objects/cone.cpp

HEADERS  += GUI/mainwindow.h \
    Render/render.h \
    Objects/camera.h \
    Objects/object3d.h \
    Objects/light.h \
    Objects/sphere.h \
    Objects/plane.h \
    Objects/box.h \
    Objects/cylinder.h \
    Render/material.h \
    Render/color.h \
    Render/ray.h \
    Render/scene.h \
    Render/canvas.h \
    Math/vec4.h \
    Math/mtx4.h \
    GUI/imagecreator.h \
    GUI/filemanager.h \
    Objects/boundingbox.h \
    Render/texture.h \
    Objects/pontuallight.h \
    Objects/cone.h

FORMS    += GUI/mainwindow.ui

RESOURCES += \
    Resources.qrc
