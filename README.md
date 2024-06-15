# Selected topics in programming exam project

## Building on nix based systems
```bash
    nix build 'github:Mast3rwaf1z/sp-exam#default?submodules=1'
    nix run 'github:Mast3rwaf1z/sp-exam#default?submodules=1'
```

## Building using cmake
```bash
    git clone https://github.com/Mast3rwaf1z/sp-exam --recurse-submodules
    cmake -B build
    cmake --build build
    ./build/main
```