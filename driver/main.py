#!/usr/bin/python2.7
import sys
import serial
import serial.tools.list_ports
from PyQt4 import QtCore, QtGui
from interface.arduino import Ui_arduino

class Client(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_arduino()
        self.ui.setupUi(self)
        self.setWindowIcon(QtGui.QIcon('interface/logo.jpg'))
        self.ui.error.setStyleSheet('color: red')
        self.ui.cancelButton.setVisible(False)
        self.ui.confirmButton.setVisible(False)
        self.ui.error.setVisible(False)
        self.ui.url.setVisible(False)
        self.ui.password.setVisible(False)
        self.ui.urlField.setVisible(False)
        self.ui.passwordField.setVisible(False)
        self.ser = None
        self.refresh()

    def add(self):
        if self.ui.loginList.count() == 10:
            self.throwError('Memory is full')
            return
        self.ui.cancelButton.setVisible(True)
        self.ui.confirmButton.setVisible(True)
        self.ui.url.setVisible(True)
        self.ui.password.setVisible(True)
        self.ui.urlField.setVisible(True)
        self.ui.passwordField.setVisible(True)
        self.ui.addButton.setVisible(False)
        self.ui.removeButton.setVisible(False)
        self.ui.refreshButton.setVisible(False)
        self.ui.loginList.setVisible(False)

    def delete(self):
        toDelete = self.ui.loginList.selectedItems()
        toDelete.reverse()
        if not toDelete: return
        for item in toDelete:
            request = b'DEL %d\n' % (self.ui.loginList.row(item))
            responce = self.arduinoRequest(request)
        self.refresh()

    def refresh(self):
        if not self.ser:
            self.connect()
            return
        self.ui.loginList.clear()
        responce = self.arduinoRequest(b'GET\n')
        if not responce:
            return
        elif responce == 'ERROR: Request Rejected\r\n':
            return
        responce = responce.split('\r\n')
        quantity = int(responce[1])
        if quantity != 0:
            responce = responce[2:]
            for i in range(quantity):
                self.ui.loginList.addItem(str(i + 1) + ') ' + responce[i].split(':')[0])

    def cancel(self):
        self.throwError('')
        self.ui.cancelButton.setVisible(False)
        self.ui.confirmButton.setVisible(False)
        self.ui.url.setVisible(False)
        self.ui.password.setVisible(False)
        self.ui.urlField.setVisible(False)
        self.ui.passwordField.setVisible(False)
        self.ui.addButton.setVisible(True)
        self.ui.removeButton.setVisible(True)
        self.ui.refreshButton.setVisible(True)
        self.ui.loginList.setVisible(True)

    def confirm(self):
        if not self.ui.urlField.text():
            self.throwError('Enter 1-10 letters for url')
            return
        request = 'ADD %s:%s\n' % (self.ui.urlField.text(), self.ui.passwordField.text())
        try:
            request = request.encode('ascii')
        except UnicodeEncodeError:
            self.throwError('Enter ASCII letters')
            return
        responce = self.arduinoRequest(request)
        self.ui.cancelButton.setVisible(False)
        self.ui.confirmButton.setVisible(False)
        self.ui.url.setVisible(False)
        self.ui.password.setVisible(False)
        self.ui.urlField.setVisible(False)
        self.ui.passwordField.setVisible(False)
        self.ui.addButton.setVisible(True)
        self.ui.removeButton.setVisible(True)
        self.ui.refreshButton.setVisible(True)
        self.ui.loginList.setVisible(True)
        self.refresh()

    def arduinoRequest(self, request):
        self.throwError('')
        try:
            self.ser.write(request)
        except Exception as e:
            self.connect()
            return ''
        responce = ''
        if request == 'GET\n':
            while not responce.endswith('DONE\r\n') and responce != 'ERROR: Request Rejected\r\n':
                responce += self.ser.read(1)
        else:
            responce = self.ser.readline()
        if responce == 'ERROR: Request Rejected\r\n':
            self.throwError('Enter sync mode')
            return
        return responce

    def throwError(self, error):
        self.ui.error.setText(QtCore.QString(error))
        if not error:
            self.ui.error.setVisible(False)
        self.ui.error.setVisible(True)

    def connect(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            if port.manufacturer == 'Arduino LLC':
                self.ser = serial.Serial(port.device, 115200, timeout=0.1)
                responce = self.arduinoRequest(b'GET\n')
                if responce == 'ERROR: Request Rejected\r\n':
                    self.throwError('Enter sync mode')
                    return
                return
        self.throwError('Connect PT')


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    client = Client()
    client.show()
    sys.exit(app.exec_())
