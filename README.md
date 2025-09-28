# EasyShell

EasyShell is a lightweight shell implementation designed to be embedded into
any CLI application as a bootstrapping layer.

## Requirements

- `libreadline`
- `meson`: tested with meson version `1.7.0`

## Build

```bash
meson setup build
meson compile -C build
```

## Limitations (Work in Progress)

- Piping is not yet supported.
- Input/output redirection is not yet supported.
- Regular expressions are not yet supported.
