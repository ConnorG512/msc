{
  description = "Music Scales flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;

    appProperties = {
      name = "msc";
      version = "1.0";
    };
  in 
  {
    packages.x86_64-linux = {
      debug = pkgs.stdenv.mkDerivation (finalAttrs: {
        pname = appProperties.name;
        version = appProperties.version;
        src = ./.;

        dontStrip = true;

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
        ];
        buildInputs = [ ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Debug"
          
        ];
      });
    };

    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [ 
        clang-tools
        cmake
        ninja
      ];

      shellHook = ''
        echo "Entering shell!"
      '';
    };
  };
}
