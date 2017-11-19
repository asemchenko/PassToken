# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'arduino.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_arduino(object):
    def setupUi(self, arduino):
        arduino.setObjectName(_fromUtf8("arduino"))
        arduino.resize(400, 400)
        arduino.setMinimumSize(QtCore.QSize(400, 400))
        arduino.setMaximumSize(QtCore.QSize(400, 400))
        self.addButton = QtGui.QPushButton(arduino)
        self.addButton.setGeometry(QtCore.QRect(30, 320, 100, 30))
        self.addButton.setObjectName(_fromUtf8("addButton"))
        self.loginList = QtGui.QListWidget(arduino)
        self.loginList.setGeometry(QtCore.QRect(75, 80, 250, 200))
        self.loginList.setMinimumSize(QtCore.QSize(250, 200))
        self.loginList.setMaximumSize(QtCore.QSize(250, 200))
        self.loginList.setFrameShape(QtGui.QFrame.StyledPanel)
        self.loginList.setFrameShadow(QtGui.QFrame.Sunken)
        self.loginList.setLineWidth(1)
        self.loginList.setMidLineWidth(0)
        self.loginList.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.loginList.setSelectionMode(QtGui.QAbstractItemView.ExtendedSelection)
        self.loginList.setLayoutMode(QtGui.QListView.SinglePass)
        self.loginList.setObjectName(_fromUtf8("loginList"))
        self.name = QtGui.QLabel(arduino)
        self.name.setGeometry(QtCore.QRect(150, 30, 100, 20))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.name.setFont(font)
        self.name.setAlignment(QtCore.Qt.AlignCenter)
        self.name.setObjectName(_fromUtf8("name"))
        self.removeButton = QtGui.QPushButton(arduino)
        self.removeButton.setGeometry(QtCore.QRect(150, 320, 100, 30))
        self.removeButton.setObjectName(_fromUtf8("removeButton"))
        self.refreshButton = QtGui.QPushButton(arduino)
        self.refreshButton.setGeometry(QtCore.QRect(270, 320, 100, 30))
        self.refreshButton.setObjectName(_fromUtf8("refreshButton"))
        self.url = QtGui.QLabel(arduino)
        self.url.setGeometry(QtCore.QRect(160, 90, 80, 20))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.url.setFont(font)
        self.url.setAlignment(QtCore.Qt.AlignCenter)
        self.url.setObjectName(_fromUtf8("url"))
        self.password = QtGui.QLabel(arduino)
        self.password.setGeometry(QtCore.QRect(160, 190, 80, 20))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.password.setFont(font)
        self.password.setAlignment(QtCore.Qt.AlignCenter)
        self.password.setObjectName(_fromUtf8("password"))
        self.passwordField = QtGui.QLineEdit(arduino)
        self.passwordField.setGeometry(QtCore.QRect(75, 220, 250, 30))
        self.passwordField.setMaxLength(30)
        self.passwordField.setEchoMode(QtGui.QLineEdit.Password)
        self.passwordField.setObjectName(_fromUtf8("passwordField"))
        self.urlField = QtGui.QLineEdit(arduino)
        self.urlField.setGeometry(QtCore.QRect(75, 120, 250, 30))
        self.urlField.setMaxLength(10)
        self.urlField.setEchoMode(QtGui.QLineEdit.Normal)
        self.urlField.setObjectName(_fromUtf8("urlField"))
        self.cancelButton = QtGui.QPushButton(arduino)
        self.cancelButton.setGeometry(QtCore.QRect(75, 280, 100, 30))
        self.cancelButton.setObjectName(_fromUtf8("cancelButton"))
        self.confirmButton = QtGui.QPushButton(arduino)
        self.confirmButton.setGeometry(QtCore.QRect(225, 280, 100, 30))
        self.confirmButton.setObjectName(_fromUtf8("confirmButton"))
        self.error = QtGui.QLabel(arduino)
        self.error.setGeometry(QtCore.QRect(100, 55, 200, 20))
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setItalic(True)
        self.error.setFont(font)
        self.error.setContextMenuPolicy(QtCore.Qt.PreventContextMenu)
        self.error.setAutoFillBackground(False)
        self.error.setStyleSheet(_fromUtf8(""))
        self.error.setAlignment(QtCore.Qt.AlignCenter)
        self.error.setObjectName(_fromUtf8("error"))

        self.retranslateUi(arduino)
        QtCore.QObject.connect(self.addButton, QtCore.SIGNAL(_fromUtf8("clicked()")), arduino.add)
        QtCore.QObject.connect(self.removeButton, QtCore.SIGNAL(_fromUtf8("clicked()")), arduino.delete)
        QtCore.QObject.connect(self.refreshButton, QtCore.SIGNAL(_fromUtf8("clicked()")), arduino.refresh)
        QtCore.QObject.connect(self.cancelButton, QtCore.SIGNAL(_fromUtf8("clicked()")), arduino.cancel)
        QtCore.QObject.connect(self.confirmButton, QtCore.SIGNAL(_fromUtf8("clicked()")), arduino.confirm)
        QtCore.QMetaObject.connectSlotsByName(arduino)

    def retranslateUi(self, arduino):
        arduino.setWindowTitle(_translate("arduino", "Form", None))
        self.addButton.setText(_translate("arduino", "Add new", None))
        self.name.setText(_translate("arduino", "Pass Token", None))
        self.removeButton.setText(_translate("arduino", "Delete", None))
        self.refreshButton.setText(_translate("arduino", "Refresh", None))
        self.url.setText(_translate("arduino", "Url", None))
        self.password.setText(_translate("arduino", "Password", None))
        self.cancelButton.setText(_translate("arduino", "Cancel", None))
        self.confirmButton.setText(_translate("arduino", "Confirm", None))
        self.error.setText(_translate("arduino", "<html><head/><body><p><span style=\" color:#ff0000;\">Error</span></p></body></html>", None))

