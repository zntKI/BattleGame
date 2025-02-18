# BattleGame

My first game in C++, made by using SFML as a graphics library.<br><br>
It is a Pokémon/Final Fantasy-like 2D battle game with a roguelike element in which the player faces opponents until defeated.

<p align="center">
  <img src="Media/demo.gif"><br/>
  *<i>Low frame rate caused by gif limitations</i>*
</p>

## Overview

Throughout the development process, I was able to apply what I had have just learnt during my C++ module;<br>
Some of the fundamental concepts being: Memory Management, CONST-ness and File I/O.

## Features

### Scenes setup

Done by utilizing a [JSON-parsing library for C++](https://github.com/nlohmann/json) and then mapping the raw data to C++ objects with the corresponding properties.

### Gameplay

Player and opponent take turns until one of them is defeated.

- **Player:**
  1. Attack
  2. Recover
 
- **Enemy:**
  1. Same ones as 'Player'
  2. Additionally, a 'Do nothing' mechanic that skips the opponent's turn

If an opponent is defeated, another one spawns until the player dies or decides to quit the session.

### High-score persistency:

A scoreboard is displayed at the start screen of the game, displaying the best results of players so far.<br>
When a player is finally defeated, his score is saved into a scoreboard with other players' scores in it.


### Assets
- **[Characters and Backgrounds](https://craftpix.net/?utm_campaign=Website&utm_source=itch.io&utm_medium=public)**
- **[UI](https://franuka.itch.io/rpg-ui-pack-demo)**
