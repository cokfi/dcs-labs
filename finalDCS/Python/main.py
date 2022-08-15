import sys
import serial as ser
import time
import PySimpleGUI as sg  # Part 1 - The import

# in this example we send a character, and receive a string in response only if the start character was 'u'
BUTTON_SIZE = (20, 1)
BUTTON_COLOR_UNPRESSED = ('white', 'black')
BUTTON_COLOR_CHOSEN = ('black', 'white')
BUTTON_COLOR_PRESSED = ('black', 'blue')
CANVAS_RESOLUTION = (480, 480)
POINT_SIZE = (4, 4)
MODE_TEXT = ["Write", "Erase", "Neutral"]

UP_THRESHOLD = 120  # Need to check real values
DOWN_THRESHOLD = -120  # Need to check real values

# COMMUNICATION MESSAGES #
EXIT_MESSAGE = 'b'
ERROR_MESSAGE = 'e'
ACKNOWLEDGE_MESSAGE = 'a'
BUTTON_PRESSED_MESSAGE = 'p'
UP_MESSAGE = 'u'
DOWN_MESSAGE = 'd'
NO_COMMAND_MESSAGE = 'n'



class MainMenu:
    def __init__(self):
        if __name__ == '__main__':
            button_1 = sg.Button("1. Motor Control", key=1, size=BUTTON_SIZE, button_color=BUTTON_COLOR_UNPRESSED)
            button_2 = sg.Button("2. Painter", key=2, size=BUTTON_SIZE, button_color=BUTTON_COLOR_UNPRESSED)
            button_3 = sg.Button("3. Stepper Calibration", key=3, size=BUTTON_SIZE, button_color=BUTTON_COLOR_UNPRESSED)
            button_4 = sg.Button("4. Script Mode", key=4, size=BUTTON_SIZE, button_color=BUTTON_COLOR_UNPRESSED)
            layout = [[button_1], [button_2], [button_3], [button_4]]
            self.window = sg.Window('DCS Final Project Main Menu', layout, resizable=True, return_keyboard_events=True)


class PainterMode:
    WRITE = 0
    ERASE = 1
    NEUTRAL = 2


class PaintCursor:
    x = CANVAS_RESOLUTION[0] // 2
    y = CANVAS_RESOLUTION[1] // 2


class Painter:
    def __init__(self, UART):
        self.UART = UART
        self.canvas = sg.Graph(CANVAS_RESOLUTION, (0, 0), CANVAS_RESOLUTION, key='CANVAS', background_color='white')
        self.cursor = PaintCursor()
        self.mode = PainterMode.NEUTRAL
        layout = [[self.canvas], [sg.Text(MODE_TEXT[self.mode], key='Mode')]]
        self.window = sg.Window("Painter", layout, return_keyboard_events=True)

    def moveCursor(self, dx, dy):
        if self.mode == PainterMode.NEUTRAL:
            self.canvas.draw_point((self.cursor.x, self.cursor.y), size=20, color='white')

            self.window['CANVAS'].update()

        self.cursor.x += dx
        self.cursor.y += dy
        if self.mode == PainterMode.WRITE:
            self.canvas.draw_point((self.cursor.x, self.cursor.y), 5, color='black')

        elif self.mode == PainterMode.ERASE:
            self.canvas.draw_point((self.cursor.x, self.cursor.y), 10, color='white')
        else:
            self.canvas.draw_point((self.cursor.x, self.cursor.y), size=10, color='blue')

    def changeMode(self):
        if self.mode == PainterMode.NEUTRAL:
            self.canvas.draw_point((self.cursor.x, self.cursor.y), size=20, color='white')

        self.mode = (self.mode + 1) % 3
        self.window['Mode'].update(MODE_TEXT[self.mode])

    def paint(self):

        self.UART.send('2')
        while True:
            # time.sleep(0.1)
            self.window.finalize()
            # self.window.bind('<Up>','-UP-')
            # self.window.bind('<Down>','-DOWN-')
            # self.window.bind('<Left>','-LEFT-')
            # self.window.bind('<Right>','-RIGHT-')
            # self.window.bind('<Return>','-SHIFT_MODE-')

            dx = 0
            dy = 0

            command = self.UART.getCommand()
            self.window.finalize()
            #print(command)
            if command == BUTTON_PRESSED_MESSAGE:
                self.changeMode()
                self.window.finalize()
            else:
                dx, dy = self.UART.getJoystickRead()
                # print("x = ",dx,", y = ",dy)

                self.window.finalize()

            # if event=="-UP-":
            # 	dy = 1
            #
            # elif event=='-DOWN-':
            # 	dy = -1
            #
            # elif event=='-LEFT-':
            # 	dx = -1
            #
            # elif event=='-RIGHT-':
            # 	dx = 1
            #
            # elif event=='-SHIFT_MODE-':
            # 	self.changeMode()

            self.moveCursor(dx, dy)
        self.window.close()


class UART:
    def __init__(self):
        self.channel = ser.Serial('COM3', baudrate=9600, bytesize=ser.EIGHTBITS, parity=ser.PARITY_NONE,
                                  stopbits=ser.STOPBITS_ONE,
                                  timeout=1)  # timeout of 1 sec so that the read and write operations are blocking,  # after the timeout the program continues
        self.channel.reset_input_buffer()
        self.channel.reset_output_buffer()

    def send(self, message):
            inChar = message
            bytesChar = bytes(inChar, 'ascii')
            self.channel.write(bytesChar)

    def receive(self):

        if self.channel.in_waiting > 0:  # while the input buffer isn't empty
            line = self.channel.read() #_until(terminator='\n')  # read  from the buffer until the terminator is received,
            return line  # maybe return number_hex instead?

    def getCommand(self):
        line = self.receive()
        if (line != None):
            msg = chr(line[0])
            # time.sleep(0.5)
            self.send(ACKNOWLEDGE_MESSAGE)
            return msg




    # TODO - Add a way to translate command, maybe 'receive()' should output the bytes without translation

    def getData(self):
        # self.send('d')
        line = self.receive()
        msg = int.from_bytes(line, "big", signed=True)  # format is int.from_bytes(byte array, endian, signed/unsigned)
        # time.sleep(0.05)
        return msg

    def getJoystickRead(self):
        self.send('x')
        x_bytes = self.receive()
        # time.sleep(0.1)
        self.send(ACKNOWLEDGE_MESSAGE)
        if x_bytes is None:
            x = 0
        else:
            bytestring = x_bytes.hex()
            x = (int(bytestring,base = 16) -127)/20
            # x = int.from_bytes(x_bytes, "big", signed=True)/100
        # time.sleep(0.25)
        #print("x= ", x)
        self.send('y')
        y_bytes = self.receive()
        if y_bytes is not None:
            self.channel.reset_input_buffer()
        # time.sleep(0.1)
        self.send(ACKNOWLEDGE_MESSAGE)
        if y_bytes is None:
            y = 0
        else:
            bytestring = y_bytes.hex()
            y = (127 - int(bytestring, base=16)) /20
            # y = int.from_bytes(y_bytes, "big", signed=True)/100
            #print("y= ", y)
        return x, y


class MotorControlApp:
    def __init__(self, UART):
        self.UART = UART
        layout = [sg.Text("Control Motor Using Joystick")]
        self.window = sg.Window("Motor Control", layout, return_keyboard_events=True)

    def run(self):
        while (True):
            event, values = self.window.read()
            if event in (sg.WIN_CLOSED, 'Exit'):
                self.UART.send(EXIT_MESSAGE)
                break


class MotorCalibrationApp:
    def __init__(self, UART):
        self.UART = UART

        layout = [sg.Text("Press joystick button to start the motor"),
                  sg.Text("Press again to stop when reaching 0 angle"),
                  [sg.Text('FCS'), sg.Text(key='Nphi')]]
        self.window = sg.Window("Motor Control", layout, return_keyboard_events=True)

    def run(self):
        while (True):
            fcs = self.UART.getData()  # Full Circle Steps
            nphi = self.UART.getData()  # Nominal Angle
            command = self.UART.getCommand()
            if (command == EXIT_MESSAGE):
                break


def main():
    main_menu = MainMenu()
    current_choice = 1
    uart = UART()
    uart.send(ACKNOWLEDGE_MESSAGE)


    while True:
        #event, values = main_menu.window.read()

        # main_menu.window.bind('<Up>','-UP-')
        # main_menu.window.bind('<Down>','-DOWN-')
        # main_menu.window.bind('<Return>','-CHOOSE-')

        #if event in (sg.WIN_CLOSED, 'Exit'):
        #    break

        # dx,dy = uart.getJoystickRead()

        main_menu.window.finalize()
        command = uart.getCommand()
        if command is not None:
            uart.channel.reset_input_buffer()


        if command == UP_MESSAGE:
            if current_choice > 1:
                main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
                current_choice = current_choice - 1
                print(current_choice)
        # if event=="-UP-":
        # 	if current_choice>1:
        # 		main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
        # 		current_choice = current_choice-1
        elif command == DOWN_MESSAGE:
            if current_choice < 4:
                main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
                current_choice = current_choice + 1
                print(current_choice)
        # elif event=='-DOWN-':
        # 	if current_choice<4:
        # 		main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
        # 		current_choice = current_choice+1
        elif command == BUTTON_PRESSED_MESSAGE:
            uart.send(ACKNOWLEDGE_MESSAGE)
            uart.send(chr(current_choice))
            if current_choice == 1:
                print("Motor Control")
                mc = MotorControlApp()
                mc.run()

            elif current_choice == 2:
                print("Painter")
                painter = Painter(uart)
                painter.paint()
            elif current_choice == 3:
                print("Motor Calibration")
                mc = MotorCalibrationApp()
                mc.run()
            else:
                print("Script Mode")
        # elif event=='-CHOOSE-':
        #
        # 	if current_choice==2:
        # 		painter = Painter()
        # 		painter.paint()

        #print(event, values)
        # ------ Process menu choices ------ #
        main_menu.window[current_choice].set_focus(force=True)
        main_menu.window[current_choice].update(button_color=BUTTON_COLOR_CHOSEN)
        time.sleep(1)

    main_menu.window.close()


if __name__ == '__main__':
    main()
