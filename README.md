# Adruino_Bullet_ctrl
Control firmware to control bullet.  To be uploaded onto subrack controller.  Arduino Mega.

Operation:
This subrack controller(U2) receives commands from the controller inside the screened enclosure(U1) via fibre links and the interface board.
This happens via the RS232 port and can thus also be directly controlled with the arduino IDE serial monitor for testing.

Commands from U1 switches U2 on via  the interface board prior to sending commands to U2 and switches U2 off after sending commands.  This ensures 
that there is no digital electronics switched on during a measurement.

Commands to be given via serial port.  

Commands:
 SW11 = SW1 in pos 1
 SW12 = SW1 in pos 2
 SW21 = SW2 in pos 1
 SW22 = SW2 in pos 2
 SW31 = SW3 in pos 1
 SW32 = SW3 in pos 2
 SW41 = SW4 in pos 1
 SW42 = SW4 in pos 2
 
 ND_0 = ND OFF
 ND_1 = ND ON 
 
 LN10 = LNA1 OFF
 LN11 = LNA1 ON

 LN20 = LNA2 OFF
 LN21 = LNA2 ON

 PARK = ALL OFF
 
 ========================
 check code to see what to do...?
 CW__= Antenna CW
 CCW_= Antenna CCW
 HOR_= Antenna HOR
 VER_= Antenna VER
 POSA=Azi Pos
 POSP=Pol Pos
========================
 
 
 Commands for Auto Mode (ADD + AFTER MODE ENTRY):
 MOD0 = MODE0 - 0.1-2  GHz high  gain  measurement
 MOD1 = MODE1 - 0.85-6  GHz high  gain  measurement
 MOD2 = MODE2 - high  gain  calibration
 MOD3 = MODE3 - 0.1-2 GHz medium  gain  measurement
 MOD4 = MODE4 - 0.85-12 GHz medium  gain  measurement
 MOD5 = MODE5 - medium  gain  calibration
 MOD6 = MODE6 - 0.85-26.5 GHz zero  gain  measurement
 MOD7 = MODE7 - zero gain calibration

TD =  SWITCH ND AT (INPUT(Hz))
ND =  PULSE ND
ND1 = SWITCH ND PN FOR INPUT(MS)
NON = ND ON
NOF = ND OFF


Rotator control:  -- this will most probably be rewritten. Too clunky but should work
analoq V: 
0 - 5.1v ----> 0 to 405 deg ----> 0 - 1023 adc
0 to 5.2v ----> 0 to 180 ----> 0 - 1023
scale factor az: 1023/405 = 2.526
scale factor pol: 1023/180 = 5.683
pinout control connector:
orange 4 rot left
w/green 2 rot right
brown 3 rot up
blue 5 rot down

w/blue 6 0 to 405 Deg
w/orange 1 0 to 180 Deg
green 8 common grnd
w/brown 7 Provides 13V to 6V DC @ 200mA
