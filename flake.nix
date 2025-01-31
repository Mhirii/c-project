{
  description = "Dev Shell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      architecture = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${architecture};
    in
    {

      devShells.${architecture}.default = pkgs.mkShell {
        packages = with pkgs;[
        gcc
        clang
        gnumake
        ncurses
        ];
        shellHook = ''
        echo "Development environment loaded"
				'';
      };
  };
}
