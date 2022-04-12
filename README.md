# CheatEngine
This repo introduces a free opensource tool for memory scanning and utilizing the pointer to modify the AmmoValue and Healthpoint in AssaultCube.


# Running the Cheat Engine
## Tested game supporting CheatEngine
[Assault Cube 1.3.0.2](https://github.com/assaultcube/AC/releases/download/v1.3.0.2/AssaultCube_v1.3.0.2_LockdownEdition.exe)

[1_bit_clicker_win.exe](https://i-am-44.itch.io/1-bit-dungeon-clicker)

## How to Test
1. Run the game above
2. Run `CheatEngine.exe -n AssaultCube` or `CheatEngine.exe -n "1bit clicker"`

## Main Menu
`Menu: (p) Pointer menu, (m)Memory search menu, (u)Unknown value scan (x)Exit`

Enter :

`p` to modify value by address pointer, `m` to memory search (exact value search), `u` to unknown value scan, `x` to exit

## Pointer Menu (For Assualt Cube). 
`Menu: (a)Update Ammo, (h)Update Health Point, (b)Back`

Enter:

`a` to update game ammo, `h` to update game health, `b` to go back.

For update ammo, you need enter the ammo amount you want. Then, the program will overwrite the value automatically.
For update health point, you need enter the health amount you want. Then, the program will overwrite the value automatically.

## Memory Search Menu (For Assualt Cube). 
`Menu: (n)New search, (c)Continue search, (m)Modify value, (l)List address, (b)Back`
Enter:
`n` to perform new search of address by specificing value, 

`c` to continue the search from preceding search result

`m` to overwrite value on the address from the search address result list

`l` to list the searched addresses

`b` to go back

`(m)Modify value` provides infinite write feature. To do that, select `y` when ifninite write option is shown. ![Screenshot 2022-04-11 185650](https://user-images.githubusercontent.com/13512755/162863585-abd6ad5f-c619-4723-b2a1-572ea7b1bd4a.png)

## Unknown Value Scan Menu (For 1bit clicker)
Unknown value scan provide extra option `(+)Scan for increased value` and `(-)Scan for decreased value`. Other options are similar to Memory menu.

`Unknown value scan: (n)New scan, (+)Scan for increased value, (-)Scan for decreased value, (m)Modify value, (l)List address, (b)Back`

`(+)Scan for increased value` will look up the addresses by search the values that is increased from the addresses list of the preceding scan.
`(-)Scan for decreased value` will look up the addresses by search the values that is decreased from the addresses list of the preceding scan.


