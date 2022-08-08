import sys
import serial as ser
import time
import PySimpleGUI as sg  # Part 1 - The import

#in this example we send a character, and receive a string in response only if the start character was 'u'
BUTTON_SIZE = (20,1)
BUTTON_COLOR_UNPRESSED = ('white','black')
BUTTON_COLOR_CHOSEN = ('black','white')
BUTTON_COLOR_PRESSED = ('black','blue')
CANVAS_RESOLUTION = (480,480)
POINT_SIZE = (4,4)
MODE_TEXT = ["Write","Erase","Neutral"]

class MainMenu:
    def __init__(self):
        if __name__=='__main__':
            button_1 = sg.Button("1. Motor Control",key=1,size=BUTTON_SIZE,button_color=BUTTON_COLOR_UNPRESSED)
            button_2 = sg.Button("2. Painter",key=2,size=BUTTON_SIZE,button_color=BUTTON_COLOR_UNPRESSED)
            button_3 = sg.Button("3. Stepper Calibration",key=3,size=BUTTON_SIZE,button_color=BUTTON_COLOR_UNPRESSED)
            button_4 = sg.Button("4. Script Mode",key=4,size=BUTTON_SIZE,button_color=BUTTON_COLOR_UNPRESSED)
            layout = [[button_1],[button_2],[button_3],[button_4]]
            self.window = sg.Window('DCS Final Project Main Menu',layout,resizable=True,return_keyboard_events=True)

class PainterMode:
    WRITE = 0
    ERASE = 1
    NEUTRAL = 2

class PaintCursor:
    x = CANVAS_RESOLUTION[0]//2
    y = CANVAS_RESOLUTION[1]//2

class Painter:
    def __init__(self):
        self.canvas = sg.Graph(CANVAS_RESOLUTION,(0,0),CANVAS_RESOLUTION,key='CANVAS',background_color='white')
        self.cursor = PaintCursor()
        self.mode = PainterMode.NEUTRAL
        layout = [[self.canvas],[sg.Text(MODE_TEXT[self.mode],key='Mode')]]
        self.window = sg.Window("Painter",layout,return_keyboard_events=True)
    
    def moveCursor(self,dx,dy):
        if self.mode==PainterMode.NEUTRAL:
            self.canvas.draw_point((self.cursor.x,self.cursor.y),size=20,color='white')
            
            self.window['CANVAS'].update()
        
        self.cursor.x += dx
        self.cursor.y += dy
        if self.mode==PainterMode.WRITE:
            self.canvas.draw_point((self.cursor.x,self.cursor.y),5,color='black')
        
        elif self.mode==PainterMode.ERASE:
            self.canvas.draw_point((self.cursor.x,self.cursor.y),10,color='white')
        else:
            self.canvas.draw_point((self.cursor.x,self.cursor.y),size=10,color='blue')
    
    def changeMode(self):
        if self.mode==PainterMode.NEUTRAL:
            self.canvas.draw_point((self.cursor.x,self.cursor.y),size=20,color='white')
    
        self.mode = (self.mode+1)%3
        self.window['Mode'].update(MODE_TEXT[self.mode])
    
    def paint(self):
        
        while True:
            event,values = self.window.read()
            
            self.window.bind('<Up>','-UP-')
            self.window.bind('<Down>','-DOWN-')
            self.window.bind('<Left>','-LEFT-')
            self.window.bind('<Right>','-RIGHT-')
            self.window.bind('<Return>','-SHIFT_MODE-')
            
            dx = 0
            dy = 0
            
            if event in (sg.WIN_CLOSED,'Exit'):
                break
            if event=="-UP-":
                dy = 1
            
            elif event=='-DOWN-':
                dy = -1
            
            elif event=='-LEFT-':
                dx = -1
            
            elif event=='-RIGHT-':
                dx = 1
            
            elif event=='-SHIFT_MODE-':
                self.changeMode()
            
            self.moveCursor(dx,dy)
            print(event)  # ------ Process menu choices ------ #
        
        self.window.close()

def main():
    main_menu = MainMenu()
    current_choice = 1
    while True:
        event,values = main_menu.window.read()
        
        main_menu.window.bind('<Up>','-UP-')
        main_menu.window.bind('<Down>','-DOWN-')
        main_menu.window.bind('<Return>','-CHOOSE-')
        
        if event in (sg.WIN_CLOSED,'Exit'):
            break
        if event=="-UP-":
            if current_choice>1:
                main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
                current_choice = current_choice-1
        
        elif event=='-DOWN-':
            if current_choice<4:
                main_menu.window[current_choice].update(button_color=BUTTON_COLOR_UNPRESSED)
                current_choice = current_choice+1
        
        elif event=='-CHOOSE-':
            
            if current_choice==2:
                painter = Painter()
                painter.paint()
        
        print(event,values)
        # ------ Process menu choices ------ #
        main_menu.window[current_choice].set_focus(force=True)
        main_menu.window[current_choice].update(button_color=BUTTON_COLOR_CHOSEN)
    
    main_menu.window.close()
    
    # Finish up by removing from the screen  # window.close()

# s = ser.Serial('COM3',baudrate=9600,bytesize=ser.EIGHTBITS,parity=ser.PARITY_NONE,stopbits=ser.STOPBITS_ONE,
#                timeout=1)  # timeout of 1 sec so that the read and write operations are blocking,
# # after the timeout the program continues
# enableTX = True
# isGetDelay = False
# # clear buffers
# s.reset_input_buffer()
# s.reset_output_buffer()
# while 1:
# 	while s.in_waiting>0:  # while the input buffer isn't empty
# 		line = s.read_until()  # read  from the buffer until the terminator is received,
# 		# readline() can also be used if the terminator is '\n'
# 		print(line.decode("ascii"))
# 		if s.in_waiting==0:
# 			enableTX = True
# 	while s.out_waiting>0 or enableTX:  # while the output buffer isn't empty
# 		inChar = input("Enter char:")
# 		if isGetDelay:
# 			bytesChar = bytes(inChar+'\n','ascii')
# 		else:
# 			bytesChar = bytes(inChar,'ascii')
# 		s.write(bytesChar)
# 		if isGetDelay:
# 			time.sleep(0.25)  # delay for accurate read/write operations on both ends
# 		if s.out_waiting==0 and ('1' or '2' or '4' or '3' or '0' in inChar):
# 			if '4' in inChar:
# 				isGetDelay = True
# 			else:
# 				isGetDelay = False
# 			enableTX = False

if __name__=='__main__':
    main()
