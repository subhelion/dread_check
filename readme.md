# DRAUGB

## Requirements

### Build requirements
- Windows 10 (tested on version 2004)
- MSVC (included in [Visual Studio 2019 Build Tools](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2019)) or Clang (WIP)

### Development requirements
- [Visual Studio Code](https://code.visualstudio.com/)
- Bash (included in [Git for Windows](https://gitforwindows.org))

### Optional development tools
- [Visual Studio Code Cpp Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [Windows Sandbox](https://docs.microsoft.com/en-us/windows/security/threat-protection/windows-sandbox/windows-sandbox-overview)
- [ShellCheck](https://www.shellcheck.net)

## Art

### Asset tools

These can edit and save dds textures:

- [Paint.NET](http://www.getpaint.net)
- Visual Studio Image Editor (Individual Components > Games and Graphics > Image and 3D model editors)

## Development

### Starting a development environment
1. Open the `draugb` folder in VS Code.
2. Open the integrated terminal.
3. Run the `start` script:

```sh
script/start
```

> **NOTE** <p> The `start` script assumes that the `A:` drive is available for `subst`

### Development scripts

```sh
# (re)start code with tools
start

# install vcpkg
vcpkg

# install dependencies with vcpkg
install

# rebuild local/vend
vend

# assets
script/data/font
script/data/skybox

# checks
script/check/data
script/check/script
script/check/shader

# building

build
build debug
build profile
build release

# running

run
run --debug
run --headless

# publishing

publish
publish staging
publish production
```

## Zed

```
void main_init();
void main_size();
void main_idle();
void main_start();
void main_step();
void main_draw();
void main_on_system_event( app_system_event );
void main_exit();
void main_midi( midi_event event );
```
