# arduino-door-lock-thinkerCad-simulation
Followed what's in the assignement document and added extra things such as the character selecter to modify or delete the selected char.

## How does it work :

You enter a password. Upon entering the password, you verify it by clicking '#'. If the entered password is correct, you gain access, and the door is opened. Otherwise, you are denied access. In case of denial, you can reset by clicking 'A'.

You can click on '*' to iterate over every character entered, allowing you to point to any character you wish. Once you've selected your desired character, you have two options:
* Click 'D' to delete it.
* Click 'C' to modify it. However, there's a minor issue where sometimes you may need to click more than once until the click is registered, and the new character is displayed on the LCD in place of the old one.

### In summary:
    '#' to verify the password and open the door.
    'A' to reset in case the password is incorrect.
    '*' to iterate over each character until you reach the desired one.
    'C' to modify the selected character.
    'D' to delete the selected character.

## Simulation :
#### [ThinkerCad simulation Link](https://www.tinkercad.com/things/krV00fKucOk-7-door-lock-keypad-servo-lcd)
![ThinkerCad simulation](https://github.com/badrhrm/arduino-door-lock-thinkerCad-simulation/assets/106437361/68cff6cf-39cd-4e14-a5ec-18e4bdd1a84e)
