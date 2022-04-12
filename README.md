# CheatEngine
This repo introduces a free opensource tool for memory scanning and utilizing the pointer to modify the AmmoValue and Healthpoint in AssaultCube.

## Memory scanner
The game parameters such as Ammo and health points save by variable in memory. In case an adversary can have access to this parameter, they can change the game parameters. This is the basic logic of all cheat engines.

## Developing Environment

## Tool function
Our tool offer to features:
- scanning the process memory
- search address by value
- search address by unknown value
- using a pointer to modify the game variables

## Start this program
To start the program, run below command with the winodw name of the process / game.

`./cheat_engine -n [Windows name]`

## Main Menu
Enter `p` to use pointer menu, `m` to memory search menu, `u` to unknown value scan and `x` to exit.

`Menu: (p) Pointer menu, (m)Memory search menu, (u)Unknown value scan (x)Exit`

## Pointer Menu (This menu is game Assualt Cube specific). 
You can download Assualt Cube from (https://assault.cubers.net/download.html)
Enter `a` to update game ammo, `h` to update game health, and `b` to go back.

`Menu: (a)Update Ammo, (h)Update Health Point, (b)Back`

For update ammo, you need enter the ammo amount you want. Then, the program will overwrite the value automatically.
For update health point, you need enter the health amount you want. Then, the program will overwrite the value automatically.

## Memory Menu 
Enter `n` to perform new search of address by specificing value, `c` to continue the search from preceding search result, `m` to overwrite value on the address from the search address result list, `l` to list the searched addresses and `b` to go back.
`Menu: (n)New search, (c)Continue search, (m)Modify value, (l)List address, (b)Back`

`(m)Modify value` provides infinite write feature. To do that, select `y` when ifninite write option is shown. ![Screenshot 2022-04-11 185650](https://user-images.githubusercontent.com/13512755/162863585-abd6ad5f-c619-4723-b2a1-572ea7b1bd4a.png)

## Unknown Value Scan Menu 
Unknown value scan provide extra option `(+)Scan for increased value` and `(-)Scan for decreased value`. Other options are similar to Memory menu.

`Unknown value scan: (n)New scan, (+)Scan for increased value, (-)Scan for decreased value, (m)Modify value, (l)List address, (b)Back`

`(+)Scan for increased value` will look up the addresses by search the values that is increased from the addresses list of the preceding scan.
`(-)Scan for decreased value` will look up the addresses by search the values that is decreased from the addresses list of the preceding scan.


