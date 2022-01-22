from lcd import LcdNokia

test = LcdNokia(11,12,5,2,3)
test.sendCmd('\x21\xB8\x04\x14\x20\x0C')
test.sendCmd('\x20\x80\x40')
test.clear()
test.sendData('\x1F\x05\x07')