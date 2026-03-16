*This project has been created as part of the 42 curriculum by mdalkili, makboga.*

---

# cub3D

A first-person 3D maze game in C, inspired by Wolfenstein 3D, built with raycasting.

---

## Description

**cub3D** renders a 3D perspective from a 2D map using the **DDA raycasting** technique — the same method behind the earliest 3D games. The engine casts one ray per screen column, calculates wall distances, and draws textured wall slices to simulate depth. The **MiniLibX** library handles window creation and direct pixel drawing.

The scene is defined by a `.cub` file containing:
- Paths to four `.xpm` wall textures (North, South, West, East)
- Floor and ceiling colors in `R,G,B` format
- A 2D grid map made of walls (`1`), floors (`0`), and a player start position (`N`/`S`/`E`/`W`)

Key technical aspects:
- **Parsing:** Multi-pass `.cub` file parser with full input validation
- **Map validation:** Enclosed-map check, wall-hole detection, player position rules
- **Events:** Held-key state machine for smooth movement
- **Memory:** All allocations freed on exit; tested with Valgrind

---

## Instructions

### Requirements

- Linux with X11
- `gcc` / `cc`, `make`
- `libx11-dev`, `libxext-dev`, `zlib1g-dev`

```bash
sudo apt-get install -y gcc make libx11-dev libxext-dev zlib1g-dev
```

### Compilation

```bash
make        # build
make re     # rebuild from scratch
make clean  # remove object files
make fclean # remove objects + binary
```

### Running

```bash
./cub3D <path/to/map.cub>
```

```bash
./cub3D maps/good/subject_map.cub
./cub3D maps/good/dungeon.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |

### Map Format

A valid `.cub` file must declare all six identifiers (`NO`, `SO`, `WE`, `EA`, `F`, `C`) before the map grid. The map must be fully enclosed by walls and contain exactly one player character.

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

### Memory Check

```bash
make run map=maps/good/subject_map.cub
```

Runs with `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes`.

---

## Resources

### References

| Resource | URL | Used For |
|----------|-----|----------|
| **Lode's Raycasting Tutorial** | https://lodev.org/cgtutor/raycasting.html | Core raycasting algorithm: DDA traversal, wall distance, wall height projection (`draw_three_d.c`) |
| **Lode's Raycasting — Textures** | https://lodev.org/cgtutor/raycasting2.html | Texture coordinate calculation per wall column (`draw_texture.c`) |
| **MiniLibX Docs (42)** | https://harm-smits.github.io/42docs/libs/minilibx | `mlx_get_data_addr`, `mlx_hook`, `mlx_loop` — used in `start.c`, `events.c`, `get_xpm_files.c` |
| **MiniLibX Linux Source** | https://github.com/42Paris/minilibx-linux | Bundled graphics library (`src/game/minilibx-linux/`) |
| **DDA Algorithm** | https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm) | Grid-traversal math behind the `t_dda` struct in `draw_three_d.c` |

### AI Usage

AI tools were used only for minor testing and quick reference during development.
All implementation and project logic were written by the authors.
