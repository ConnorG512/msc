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
      path = ./.;
    };
  in 
  {
    packages.x86_64-linux = {
      debug = pkgs.gcc16Stdenv.mkDerivation (finalAttrs: {
        pname = appProperties.name;
        version = appProperties.version;
        src = appProperties.path;

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

      release = pkgs.gcc16Stdenv.mkDerivation (finalAttrs: {
        pname = appProperties.name;
        version = appProperties.version;
        src = appProperties.path;

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
        ];
        buildInputs = [ ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];
      });

      relWithDebugInfo = pkgs.gcc16Stdenv.mkDerivation (finalAttrs: {
        pname = appProperties.name;
        version = appProperties.version;
        src = appProperties.path;
        
        dontStrip = true;

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
        ];
        buildInputs = [ ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];
      });
    };

    devShells.x86_64-linux.default = pkgs.mkShell.override{ stdenv = pkgs.gcc16Stdenv; } {
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
