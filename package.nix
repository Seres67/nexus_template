{
  cmake,
  stdenv,
}:
stdenv.mkDerivation {
  pname = ""; # TODO: change this
  version = "0.0.0.0";
  src = ./.;

  nativeBuildInputs = [
    cmake
  ];

  installPhase = ''
    mkdir -p $out/lib
    cp ./*.dll $out/lib
  '';
}
