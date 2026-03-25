*This project has been created as part of the 42 curriculum by marada, jobraga-.*

# cub3D 🎮

## Description

cub3D is a first-person 3D maze exploration game inspired by the legendary **Wolfenstein 3D**, the world's first FPS. Built entirely in C using the **MiniLibX** graphics library, it uses **raycasting** to simulate a 3D perspective from a 2D map.

The player navigates through a maze defined by a `.cub` configuration file, which specifies wall textures, floor/ceiling colors, and the map layout. The project demonstrates core concepts in computer graphics, math, and low-level C programming.

### Features

- **Raycasting engine** — smooth 3D rendering of walls with directional textures (N/S/E/W)
- **Multiple visual themes** — switch between 4 themes at runtime (keys `1`–`4`)
- **Doors** — interactive openable/closeable doors (`A` tiles) via the `F` key
- **Fireball projectiles** — shoot fireballs with `E`, with collision detection
- **Speed gear system** — toggle movement speed with `N`
- **Minimap** — real-time 2D overhead map in the corner
- **Smooth collision detection** — per-corner bounding-box collision for all movement directions

---

## Instructions

### Requirements

- Linux (tested on Ubuntu)
- `cc` (GCC or Clang)
- MiniLibX for Linux (`mlx_linux/` — included or must be compiled separately)
- Xorg development libraries: `libXext`, `libX11`

### Compilation

```bash
make
```

This will compile the `libftprintf` dependency and then the main executable `cub3d`.

To clean object files:
```bash
make clean
```

To fully clean (including binary):
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Running

```bash
./cub3d <path/to/map.cub>
```

Example:
```bash
./cub3d maps/map1.cub
```

Or using the shortcut:
```bash
make run
```

### Map Format (`.cub`)

The configuration file must include, **before** the map:

| Identifier | Description | Example |
|---|---|---|
| `NO` | North wall texture path (`.xpm`) | `NO textures/wall_NO.xpm` |
| `SO` | South wall texture path | `SO textures/wall_SO.xpm` |
| `WE` | West wall texture path | `WE textures/wall_WE.xpm` |
| `EA` | East wall texture path | `EA textures/wall_EA.xpm` |
| `F` | Floor color (R,G,B) | `F 10,8,16` |
| `C` | Ceiling color (R,G,B) | `C 120,90,30` |

**Map characters:**
- `1` — Wall
- `0` — Empty space
- `N/S/E/W` — Player spawn position and initial facing direction
- `A` — Door (closed)
- `F` — Door (open) *(set at runtime)*

The map must be enclosed by walls (`1`) and appear at the end of the file.

### Controls

| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera left / right |
| `F` | Interact with door |
| `E` | Shoot fireball |
| `N` | Shift gear (speed toggle) |
| `M` | Mini_map |
| `1` `2` `3` `4` | Switch visual theme |
| `Q` / `ESC` | Quit |

---

## Resources

### Raycasting & Graphics

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the essential reference for DDA-based raycasting
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) — the original FPS for historical context
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — unofficial but thorough MiniLibX guide
- [42 Docs – MiniLibX Linux](https://github.com/42Paris/minilibx-linux) — official MiniLibX Linux distribution

### Math

- [Trigonometry for Game Developers – GameDev.net](https://www.gamedev.net/tutorials/programming/math-and-physics/)
- [Digital Differential Analysis (DDA) – Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))

### AI Usage

AI (Claude) was used during this project for the following:

- **Debugging** collision detection edge cases in the bounding-box movement system
- **Explaining** raycasting math (DDA step calculation, wall-hit side detection, texture coordinate mapping)
- **Refactoring suggestions** for splitting large functions to comply with the 42 Norm (25-line function limit)
- **Writing this README**

AI was used as a learning and debugging aid. All code was written and understood by the project authors.