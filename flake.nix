{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/2c8d3f48d33929642c1c12cd243df4cc7d2ce434";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }@inputs:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        common = with pkgs; {
          bazel = bazel_7;
          jdk = jdk;
        };
      in
      {
        devShells.default = with pkgs;
          pkgs.mkShell {
            packages = with pkgs; [
              git
              common.bazel
              common.jdk
              bash

              # For buildifier, buildozer.
              bazel-buildtools
              bant
              gdb
            ];

            shellHook = ''
              exec bash
            '';
          };
      }
    );
}
