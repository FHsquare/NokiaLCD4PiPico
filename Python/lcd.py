from machine import SPI
from machine import Pin

class LcdNokia:
    def __init__(self,rst,cmd,ce,clk,tx):
        self._clk = Pin(clk)
        self._tx = Pin(tx)
        self._rst = Pin(rst, Pin.OUT)
        self._cmd = Pin(cmd, Pin.OUT)
        self._ce = Pin(ce, Pin.OUT)
        self._rst.value(0)
        self._spi = SPI(0, sck=self._clk, mosi=self._tx)
        self._rst.value(1)


    def sendCmd(self,cmdStr):
        self. _cmd.value(0)
        self._ce.value(0)
        self._spi.write(cmdStr) #('\x21\xB8\x04\x14\x20\x0C')
        self._ce.value(1)
    
    def sendData(self,dataStr):
        self._cmd.value(1)
        self._ce.value(0)
        self._spi.write(dataStr) #('\x20\x80\x40')
        self._ce.value(1)
    
    def clear(self):
        self._cmd.value(1)
        self._ce.value(0)
        for x in range(0,504):
            self._spi.write('\x00')
        self._ce.value(1)
        
#cmd.value(1)
#ce.value(0)
#spi.write('\x1F\x05\x07')
#ce.value(1)
#cmd.value(0)
#ce.value(0)
#spi.write('\xE0')
#ce.value(1)