{
  description = "myengine dev environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc
          glfw
          xorg.libX11
          xorg.libXrandr
          xorg.libXi
          xorg.libXxf86vm
          xorg.libXcursor
        ];
      };
    };
}
