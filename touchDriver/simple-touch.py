# touch driver

from time import sleep
import MPR121
import serial
import copy
import vlc

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
ser = serial.Serial('/dev/ttyACM0', 9600)

p = vlc.MediaPlayer('/home/pi/Documents/grapheneHackathon/touchDriver/mp3/Car Horn Honk 1-SoundBible.com-248048021.wav')

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
          # print ("electrode {0} was just touched".format(i))
        elif sensor.is_new_release(i):
          states[i] = 0
          '''
          for j in previous:
            if i == 0:
              output = b'%d' %(i+10)
              #ser.write(output)
            elif j == i:
              output = b'%d' %(j+10)
              ser.write(output)
          '''
          # print ("electrode {0} was just released".format(i))
      print(states)
      #count = 0
      #for i in range(1,len(states)):
        #if states[0] and states[i]:
          #ser.write(str(i))
          #print("finger {0}".format(i))
      
      
  #    print("prev: {}".format(previous))
      for i in range(1, len(states)):
        if states[0] and states[i]:
          if states[i] != previous[i] or states[0] != previous[0]:
            #output = b'%d' %i
            ser.write(str(i))
            #count += 1
            print("finger {0}".format(i), states)
            if i == 2 or i == 0:
              if states[2] == 1:
                print('BOOP')
                p.play()
      previous=copy.deepcopy(states)
    
    sleep(0.01)
  except KeyboardInterrupt:
    ser.close()
    running = False
  
