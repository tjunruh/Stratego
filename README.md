```
_____/\\\\\\\\\\\______________________________________________________________________________________________________
 ___/\\\/////////\\\____________________________________________________________________________________________________
  __\//\\\______\///______/\\\_______________________________________/\\\_______________________/\\\\\\\\________________
   ___\////\\\__________/\\\\\\\\\\\__/\\/\\\\\\\___/\\\\\\\\\_____/\\\\\\\\\\\_____/\\\\\\\\___/\\\////\\\_____/\\\\\____
    ______\////\\\______\////\\\////__\/\\\/////\\\_\////////\\\___\////\\\////____/\\\/////\\\_\//\\\\\\\\\___/\\\///\\\__
     _________\////\\\______\/\\\______\/\\\___\///____/\\\\\\\\\\_____\/\\\_______/\\\\\\\\\\\___\///////\\\__/\\\__\//\\\_
      __/\\\______\//\\\_____\/\\\_/\\__\/\\\__________/\\\/////\\\_____\/\\\_/\\__\//\\///////____/\\_____\\\_\//\\\__/\\\__
       _\///\\\\\\\\\\\/______\//\\\\\___\/\\\_________\//\\\\\\\\/\\____\//\\\\\____\//\\\\\\\\\\_\//\\\\\\\\___\///\\\\\/___
        ___\///////////_________\/////____\///___________\////////\//______\/////______\//////////___\////////______\/////_____
```

<a href="https://github.com/tjunruh/Stratego/actions/workflows/pipeline.yml"><img src="https://img.shields.io/github/actions/workflow/status/tjunruh/Stratego/pipeline.yml?label=build&branch=main"></a>

This is the two player board game of Stratego. Here, it is implemented as a console application.

# Windows

The game can be installed by double clicking on the setup executable in the Windows_Installation folder. Note that you most likely will have to run the game as administrator when you start the game in order to save games later.

# Linux

You will need to install the ncurses library if you do not already have it. Run the command below to install it.

```shell
sudo apt-get install libncurses5-dev libncursesw5-dev
```

Simply clone this repository and run the following command:

```shell
make
```

Then enter

```shell
make run
```

# Game Instructions

On entering, you may need to widen the terminal to properly see the title. To see controls pressing 'h' will display controls in most cases.
