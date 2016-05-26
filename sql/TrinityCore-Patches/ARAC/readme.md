In its current state, the ARAC's world.sql needs to be mysql inserted using -f
to get it to update properly (otherwise you get fatal warnings about duplicate
entries). So: mysql -u root -p(password) -f world < world.sql

The additional world-playercreateinfo.sql is an OPTIONAL update to the starting
areas for some of the new race/class combos that don't have 
trainers in their normal starting areas.
