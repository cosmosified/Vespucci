TEMPLATE = subdirs
SUBDIRS = VespucciLibrary Vespucci Test
QT       += core gui
QT       += widgets printsupport
QT       += svg
!win32: CONFIG   += shared debug_and_release c++11
win32: CONFIG += shared release force_debug_info c++11
win32: DEFINES += ARMA_32BIT_WORD
Vespucci.depends = VespucciLibrary
Test.depends = Vespucci VespucciLibrary


