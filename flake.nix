{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system: let
    pkgs = nixpkgs.legacyPackages.${system};
    tools = [
      pkgs.gcc8 # Version used in AU Linux Lab
    ];
    mkCppApp = { name, src, main }: pkgs.stdenv.mkDerivation {
      inherit name system src;
      nativeBuildInputs = tools;
      buildPhase = "g++ -Wall ${main}";
      installPhase = ''
      mkdir -p $out/bin
      cp a.out $out/bin/${name}
      chmod +x $out/bin/${name}
      '';
    };
  in {
    devShells.default = pkgs.mkShell {
      nativeBuildInputs = tools;
      shellHook = ''
      export PS1="\n[\e[1;32m\[nix develop:\w]\$\e[0m "
      '';
    };
    packages.project1 = mkCppApp {
      name = "project1";
      main = "project1_Buckley_bmb0136.cpp";
      src = ./src;
    };
  });
}
