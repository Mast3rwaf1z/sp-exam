{
    description = "Selected Topics in Programming exam project";

    inputs = {
        nixpkgs.url = "nixpkgs/nixos-24.05";
    };

    outputs = { self, nixpkgs }: let 
        system = "x86_64-linux";
        pkgs = import nixpkgs {inherit system;};

        default_package = (executable: pkgs.stdenv.mkDerivation {
            name = "SP";
            src = ./.;
            buildInputs = with pkgs; [cmake];
            installPhase = ''
                mkdir -p $out/bin
                ${pkgs.cmake}/bin/cmake --build .
                cp ${executable} $out/bin
                ln $out/bin/${executable} $out/bin/SP
            '';

        });
    in {
        devShells.${system}.default = pkgs.mkShell {
            packages = with pkgs; [ cmake gnuplot ];
        };
        packages.${system} = {
            default = default_package "main";
            benchmark = default_package "benchmark";
            example = default_package "example";
        };

    };
}
