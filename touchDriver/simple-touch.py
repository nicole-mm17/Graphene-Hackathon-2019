# touch driver

from time import sleep
import MPR121
import serial
import copy
import vlc
import pygame

file='/home/pi/Documents/grapheneHackathon/touchDriver/mp3/example.mp3'
pygame.init()
pygame.mixer.init()
pygame.mixer.music.load(file)

try:
  sensor = MPR121.begin()
except Exception as e:
  print (e)
  sys.exit(1)

# this is the touch threshold - setting it low makes it more like a proximity trigger default value is 40 for touch
touch_threshold = 20

# this is the release threshold - must ALWAYS be smaller than the touch threshold default value is 20 for touch
release_threshold = 10

# set the thresholds
sensor.set_touch_threshold(touch_threshold)
sensor.set_release_threshold(release_threshold)

#serial information
# ser = serial.Serial('/dev/ttyACM0', 9600)

# loop
states = [0] * 5
previous = [0] * 5
running = True
while running:
  try:
    if sensor.touch_status_changed():
      sensor.update_touch_data()
      for i in range(0, 5):
        if sensor.is_new_touch(i):
          states[i] = 1
        elif sensor.is_new_release(i):
          states[i] = 0
      print(states)
      for i in range(1, len(states)):
        if states[0] and states[i]:
          if states[i] != previous[i] or states[0] != previous[0]:
            # ser.write(str(i))
            print("finger {0}".format(i), states)
            if i == 4 or i == 0:
              if states[4] == 1:
                print('BOOP')
                pygame.mixer.music.play()
      previous=copy.deepcopy(states)
    
    sleep(0.01)
  except KeyboardInterrupt:
    ser.close()
    running = False
  
