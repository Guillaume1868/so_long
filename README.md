# So Long
[![42 Project Score](https://42-project-badge.glitch.me/users/gaubert/project/so_long)](https://github.com/ricardoreves/42-project-badge)
![norminette](https://github.com/Guillaume1868/so_long/workflows/norminette/badge.svg)


This is an implementation of the 42 project so_long

## subject

See the pdf to know what was my instructions

## Usage
To build, use make. It will build the included mlx library and link it with my project.

`make`

Then you can launch `./so_long map.ber`

## Map
- The map must be composed of only 5 possible characters: 0 for an empty
space, 1 for a wall, C for a collectible, E for map exit and P for the player’s
starting position.
- A map need to be rectangular and surrounded by walls ('1')
- Map must have at least one exit, one collectible, and one starting position
Map example :
```
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

## Compatibility
- My project works on MacOS with x86 and M1
- It will probably run on Linux, but untested (You will probably need to get the mlx for linux)

## final grade

100/100
