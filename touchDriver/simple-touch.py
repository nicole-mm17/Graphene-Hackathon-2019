# touch driver

from time import sleep
import MPR121
import serial

try:
  sensor = MPR121.begin()
except Exception as e:
  print (e)
  sys.exit(1)

# this is the touch threshold - setting it low makes it more like a proximity trigger default value is 40 for touch
touch_threshold = 40

# this is the release threshold - must ALWAYS be smaller than the touch threshold default value is 20 for touch
release_threshold = 20

# set the thresholds
sensor.set_touch_threshold(touch_threshold)
sensor.set_release_threshold(release_threshold)

# serial information
ser = serial.Serial('/dev/ttyACM0', 9600)

# loop
states = [0] * 5
running = True
while running:
  try:
    if sensor.touch_status_changed():
      sensor.update_touch_data()
      for i in range(0, 5):
        if sensor.is_new_touch(i):
          states[i] = 1
          # print ("electrode {0} was just touched".format(i))
        elif sensor.is_new_release(i):
          states[i] = 0
          # print ("electrode {0} was just released".format(i))
      for i in range(1, len(states)):
        if states[0] and states[i]:
          output = b'%d' %i
          ser.write(output)
          print("finger {0}".format(i))
    
    sleep(0.01)
  except KeyboardInterrupt:
    running = False
  
