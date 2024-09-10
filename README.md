# COMP 2710

Software Construction

# Build Instructions

## Nix

If you have the [Nix package manager](https://nixos.org) (with flakes enabled), you can run any project in this repo with:
```
nix run github:bmb0136/COMP-2710#project<number>
```

> Replace \<number\> with the project number to run. See `flake.nix` or run `nix flake show` for a full list

## Manual

```
g++ -Wall path/to/file.cpp
```
