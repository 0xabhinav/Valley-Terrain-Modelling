{
  description = "WASM build environment with Emscripten and GLM";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        
        # Set GLM version
        glm-version = "0.9.9.8";
        
        # Create a custom GLM package at the specific version
        glm = pkgs.glm.overrideAttrs (oldAttrs: {
          version = glm-version;
          src = pkgs.fetchFromGitHub {
            owner = "g-truc";
            repo = "glm";
            rev = glm-version;
            sha256 = "sha256-F//+3L5Ozrw6s7t4LrcUmO7sN30ZSESdrPAYX57zgr8="; # Replace with actual SHA after first run
          };
          outputs = [ "out" ]; # Only build the main output, skip documentation
                    
          installPhase = ''
            mkdir -p $out/include
            cp -r glm $out/include/
          '';
        });
        
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            emscripten
            git
            wget
            unzip
            glm
            miniserve
          ];
          
          shellHook = ''
            export GLM_VERSION="${glm-version}"
            export GLM_INCLUDE_PATH="${pkgs.glm}/include"
            
            echo "WASM build environment loaded with Emscripten and GLM ${glm-version}"
            echo "Run './build-wasm.sh' to build your project"
          '';
        };
      }
    );
}
