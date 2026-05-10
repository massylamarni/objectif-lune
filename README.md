# Getting Started

From the project root:

```sh
make
./build/prog
```

---

## Controls

### Movement

| Key | Action |
|-----|--------|
| `z` | Move along negative Z axis |
| `s` | Move along positive Z axis |
| `q` | Move along negative X axis |
| `d` | Move along positive X axis |
| `a` | Move along negative Y axis |
| `e` | Move along positive Y axis |
| `SPACE` | Activate vertical thrust |

### Camera

| Input | Action |
|-------|--------|
| LMB(hold) | Move the camera |
| RMB(click) | Rotate the LEM |
| Scroll | Zoom |

**Right-click rotation details** :

| Click position | Effect |
|----------------|--------|
| Left of window | Yaw right |
| Right of window | Yaw left |
| Top of window | Pitch forward |
| Bottom of window | Pitch backward |

### View & Debug

| Key | Action |
|-----|--------|
| `f` | Toggle debug display |
| `u` | Toggle minimap |
| `v` | Toggle model editor |

### Simulation

| Key | Action |
|-----|--------|
| `p` | Pause |
| `r` | Restart |

### OpenGL Toggles

| Key | Action |
|-----|--------|
| `h` | Toggle `GL_DEPTH_TEST` |
| `H` | Toggle `GL_CULL_FACE` |
| `l` | Toggle `GL_LIGHTING` |
| `L` | Toggle `GL_COLOR_MATERIAL` |
| `o` | Cycle polygon mode: `GL_FILL` → `GL_LINE` → `GL_POINT` |
| `O` | Cycle clear buffer: `COLOR+DEPTH` → `DEPTH only` → `COLOR only` |