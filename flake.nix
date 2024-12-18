{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils"; };

  outputs = { self, nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system: let
    pkgs = nixpkgs.legacyPackages.${system};
    tools = [
      pkgs.gcc8 # Version used in AU Linux Lab
    ];
    mkCppApp = { name, src, main, flags ? "" }: pkgs.stdenv.mkDerivation {
      inherit name system src;
      nativeBuildInputs = tools;
      buildPhase = "g++ -Wall ${main} ${flags}";
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
    packages.default = self.packages.${system}.project5;
    packages.project1 = mkCppApp {
      name = "project1";
      main = "project1_Buckley_bmb0136.cpp";
      src = ./src;
    };
    packages.project2 = mkCppApp {
      name = "project2";
      main = "project2_Buckley_bmb0136.cpp";
      src = ./src;
    };
    packages.project3 = mkCppApp {
      name = "project3";
      main = "main.cpp";
      src = ./src/project3;
    };
    packages.project4 = mkCppApp {
      name = "project4";
      main = "main.cpp";
      src = ./src/project4;
    };
    packages.project5 = mkCppApp {
      name = "project5";
      main = "project5_Buckley_bmb0136.cpp";
      src = ./src;
      flags = "-lpthread -D BANNER_ID=$(cat banner_id)";
    };
  });
}
