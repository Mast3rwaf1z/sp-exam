{
    description = "Selected Topics in Programming";

    inputs = {
        nixpkgs.url = "nixpkgs/nixos-unstable";
    };

    outputs = { self, nixpkgs }: let 
        system = "x86_64-linux";
        pkgs = import nixpkgs {inherit system;};

        default_package = pkgs.stdenv.mkDerivation {
            name = "SP";
            src = ./.;
            buildInputs = with pkgs; [cmake];
            installPhase = ''
                mkdir -p $out/bin
                ${pkgs.cmake}/bin/cmake --build .
                cp main $out/bin
                ln $out/bin/main $out/bin/SP
            '';

        };
    in {
        devShells.${system}.default = pkgs.mkShell {
            packages = with pkgs; [ cmake ];
        };
        packages.${system}.default = default_package;

    };
}
