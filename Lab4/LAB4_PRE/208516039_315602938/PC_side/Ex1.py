import sys
import serial as ser
import time

def showMenu():
    print("1. Blink RGB LED, color by color with delay of X[ms]")
    print("2. Count up onto LCD screen with delay of X[ms]")
    print("3. Count down onto LCD screen with delay of X[ms]")
    print("4. Get delay time X[ms]:")
    print("5. Potentiometer 3-digit value [v]")
    print("6. Clear LCD screen")
    print("7. Show menu")
    print("8. Sleep")



def main():
    s = ser.Serial('COM3', baudrate=9600, bytesize=ser.EIGHTBITS,
                   parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                   timeout=1)   # timeout of 1 sec so that the read and write operations are blocking,
                                # after the timeout the program continues
    enableTX = True
    isGetDelay = False
    # clear buffers
    s.reset_input_buffer()
    s.reset_output_buffer()
    while (1):
        while (s.in_waiting > 0):  # while the input buffer isn't empty
            line = s.read_until(terminator='\n')  # read  from the buffer until the terminator is received,
                                                  # readline() can also be used if the terminator is '\n'
            print(line.decode("ascii"))
            if (s.in_waiting == 0):
                enableTX = True
        while (s.out_waiting > 0 or enableTX):  # while the output buffer isn't empty
            inChar = input("Enter char:")
            if (inChar =="7"):
                showMenu()
            if (isGetDelay):
                bytesChar = bytes(inChar + '\n', 'ascii')
            else :
                bytesChar = bytes(inChar, 'ascii')
            s.write(bytesChar)
            if (isGetDelay):
                time.sleep(0.25)  # delay for accurate read/write operations on both ends
            if s.out_waiting == 0 and ('0' or '1' or '2' or '3' or '4'  or '5' or '6' or '7' or '8' or '9' in inChar):
                if '4' in inChar:
                    isGetDelay = True
                else:
                    isGetDelay = False
                enableTX = False
#in this example we send a character, and receive a string in response only if the start character was 'u'


if __name__ == '__main__':
    main()






