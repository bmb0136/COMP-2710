# COMP 2710

Software Construction

# Build Instructions

## Nix

If you have the [Nix package manager](https://nixos.org) (with flakes enabled), you can run any project in this repo with:
```
git clone https://github.com/bmb0136/COMP-2710.git
nix run .#project<number>
```

> Replace \<number\> with the project number to run. See `flake.nix` or run `nix flake show` for a full list

> Yes, I know you can run it in one command using `nix run github:bmb0136/COMP-2710#project<number>` but if this repo already exists in the nix store then it will run the one you already have (which might be outdated). To avoid this, just clone the repo to get the latest changes, then `nix run`

## Manual

```
g++ -Wall path/to/file.cpp
```

> If this does not work, see `flake.nix` for updated build instructions
