# printer

## Commands
M3 S0 - stop extrusion (0 mm/s)
M3 S1000 - full flow extrusion (100 mm/s)
M64 P0 - retract mode
M65 P0 - regular extrusion
M64 P1 - heat to target temp
M65 P1 - heat off

## Extruder
spr   = 3200 steps per revolution (1/2 microstepping on tmc22208)
gc    = 34.400 mm gear circumference
fs    = 0.0011 mm per step = gc/spr   (0.086 for 400 steps per rev)
fa    = 2.4053 mm^2 filament area
na4   = 0.1257 mm^2 nozzle area (0.4mm nozzle)
ns4   = 0.2057 mm per step = fs*fa/na4
ms    = 100 mm/s max speed
msps4 = 486.145 ~= 486 max steps per second = ms/ns4
msi   = 255 = max speed input
sc    = 1.9065 = speed coefficient 


## Links
https://github.com/phil-barrett/grblHAL-teensy-4.x/blob/master/teensy%204%20pinouts.pdf ?!?!
https://github.com/grblHAL/core
http://svn.io-engineering.com/grblHAL/html/errors_8h_source.html
https://www.grbl.org/single-post/using-the-grblhal-web-builder
https://github.com/grblHAL/core/wiki/First-Run-Grbl-Settings#input-controls
https://github.com/terjeio/grblHAL/blob/master/doc/markdown/settings.md
https://github.com/grblHAL/iMXRT1062/blob/master/grblHAL_Teensy4/src/T41U5XBB_map.h
https://github.com/grblHAL/Plugin_SD_card
https://github.com/Sienci-Labs/gsender


## Scrap
ivpr = 82.732 mm^3 input volume per revolution
na1   = 0.7854 mm^2 nozzle area (1mm nozzle) (wrong)
ns1   = 0.2634 mm per step = fs*fa/na1 (wrong)