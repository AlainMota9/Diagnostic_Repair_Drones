import serial
import time

porta = serial.Serial('/dev/ttyUSB0', 9600)


def receptortexte():
    msg = porta.read_all()
    print(msg)


def receptor():
    temp1 = porta.read_until(b'\x3b').decode('utf-8')
    time.sleep(0.1)
    ldr1 = temp1[:-1]
    temp2 = porta.read_until(b'\x21').decode('utf-8')
    time.sleep(0.1)
    ldr2 = temp2[:-1]
    print(ldr1 + "  " + ldr2)


# print(msg.decode('utf-8')) #Para decodificar o padrão b' \r\n" o b (literal byte) \r (retorno do carro) \n(nova linha)

def transmissor(msg):
    time.sleep(1.8)  # Tempo de espera entre abriar a porta e o envio de dados
    porta.write(bytes(msg, encoding='utf-8'))


while True:
     transmissor('0!150@0#0$0%0&0?0')
     time.sleep(1)
     transmissor('1!150@0#0$0%0&0?0')
     time.sleep(1)
     transmissor('0!0@0#80$0%0&0?0')
     time.sleep(1)
     transmissor('0!0@1#80$0%0&0?0')
     time.sleep(1)
     transmissor('0!0@0#0$0%80&0?0')
     time.sleep(1)
     transmissor('0!0@0#0$1%80&0?0')
     time.sleep(1)
     transmissor('0!0@0#0$0%0&0?150')
     time.sleep(1)
     transmissor('0!0@0#0$0%0&1?150')
     time.sleep(1)
     #receptor()
