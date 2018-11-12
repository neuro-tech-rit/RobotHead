# RobotHead

OpenBCI focus widget and InMoov Robot arduino code for the InMoov robot head.

Communicates over serial with the InMoov robot.

## IMPORTANT

When sending values to the InMoov robot over serial, you must be careful to hurt the servos. I hard-coded some values in to prevent this from happening as well.

### Control Mode
* 0: "Head Mode", controls which direction the head looks (x axis)
* 1: "Jaw Mode", controls the opening and closing of the jaw (currently doesn't work)
* 2: "Neck Mode", controls which direction the head looks (y axis)


HEAD (send a 0 first):
ONLY MOVE HEAD WHEN NECK = 90!!!
	50 - 100

NECK (send a 2 first):
  50-120 
