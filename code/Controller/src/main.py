from email.quoprimime import body_check
import serial
import struct
import pygame

pygame.init()
joysticks = []
clock = pygame.time.Clock()
running = True

arduino = serial.Serial(
    port='COM2', 
    baudrate=115200, 
    # timeout=.1,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,

)

mode = 0

# Min is one more than actual for vmap
x_min = -149
x_max = 150
y_min = -99
y_max = 100
z_min = 2
z_max = 200

struct_format = 'fffffff'
struct_size = struct.calcsize(struct_format)

# serial 

def main():
    x = 0
    y = 0
    z = 100 # Resting pos
    global mode

    previous = None

    print(struct_size)

    for i in range(0, pygame.joystick.get_count()):
        joysticks.append(pygame.joystick.Joystick(i))
        joysticks[-1].init()
        print("Detected controller: " + joysticks[-1].get_name())

    if(not joysticks):
        print("No Controllers Connected")
        return

    while running:
        clock.tick(60)

        # if arduino.in_waiting:
        #     message = arduino.readline()
        #     print(message)

        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                if event.axis == 1:
                   x = vmap(event.value, -1, 1, x_min, x_max)
                   if(x < 10 and x > -10): x = 0
                if event.axis == 0:
                    y = vmap(event.value, -1, 1, y_max, y_min)
                    if(y < 10 and y > -10): y = 0

                if(event.axis == 3):
                    z = vmap(event.value, -1, 1, z_max, z_min)
                    if(z < 105 and z > 95): z = 100

            if event.type == pygame.JOYHATMOTION:
                hat_x, hat_y = event.value
                if(hat_y == 1 and mode < 2):
                    mode += 1
                
                if(hat_y == -1 and mode >0):
                    mode -= 1 
        

        botdata = struct.pack(struct_format,mode, x, y, z, 0.0, 0.0, 0.0)

        if(botdata != previous):
            print(mode, x, y, z, 0.0, 0.0, 0.0)

            arduino.write(botdata)
            previous = botdata



def vmap( x,  in_min,  in_max,  out_min,  out_max):
    return (int) ((x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min)

if __name__ == "__main__":
    main()