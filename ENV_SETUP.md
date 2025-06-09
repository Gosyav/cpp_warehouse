# Programming Language II - Envairoment setup instruction

# Requirements

**Compiler**: GCC 11 \
**System**: Ubuntu 22.04 (native instalation / wsl2 / docker)
<br/><br/>

# Docker - Windows/Linux/Mac

1. Install Docker engine on your machine
2. Install VSCode on your machine
3. Look here: https://code.visualstudio.com/docs/devcontainers/containers
4. Follow tutorial from here: https://code.visualstudio.com/docs/devcontainers/tutorial but instead "New dev Container" click "Open Folder in Cointainer" - The package with workspace contains Dockerfile and .devcontainer.json, "Open Folder in Cointainer" will use it.

# Windows WSL2

1. Install WSL2 in your windows, instruction: https://learn.microsoft.com/en-us/windows/wsl/install
2. Install Ubuntu 22.04.3 LTS from MS Store, link here: https://apps.microsoft.com/detail/9pn20msr04dw?hl=en-US&gl=US
3. Install VSCode on windows with WSL extention
4. Connect from vscode to WSL
5. Follow Ubuntu 22.04 post install setup

# Ubuntu 22.04

### Required system packages install command

```
sudo apt update
sudo apt install python3-pip
sudo apt install -y gcc-11 g++-11 gdb cmake clang-format
```

### Required (or at least recommended) VsCode extensions:

```
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cpptools-extension-pack
code --install-extension ms-vscode.cpptools-themes
code --install-extension xaver.clang-format
code --install-extension matepek.vscode-catch2-test-adapter
```

# Workspace configuration

### Clang formatter

How to configure default C++ formater:

1. Open any C++ file
2. Crtl + Shift + P
3. Find 'Format document with' and press Enter
4. Select 'Configure default formatter'
5. Select 'Clang-Format'

**Formatter usage:** Ctrl + Shift + I
