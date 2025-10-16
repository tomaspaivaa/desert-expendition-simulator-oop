# Desert Expedition Simulator — C++ Project

A console-based **desert exploration and trading simulator** built entirely in **C++**, featuring **autonomous caravans**, **procedural item generation** and **turn-based gameplay**.  
This project demonstrates advanced **object-oriented programming**, **inheritance**, and **polymorphism**, bringing complex system behavior to life through a simple terminal interface.

## Overview

The simulator models a large desert world populated by **cities**, **caravans**, **barbarians**, and **random items**.  
Players command caravans to explore, trade, and survive harsh conditions while managing water, crew, and cargo.  
Barbarian caravans roam the desert autonomously, creating dynamic interactions and combat situations.

The game world is rendered textually through a **buffer-based visualization system**, ensuring smooth and efficient updates on the terminal.



## Technologies Used

- **C++17** – Core language for implementation  
- **Object-Oriented Design** – Classes, inheritance, encapsulation, and polymorphism  
- **Smart Pointers** – For memory management and resource safety  
- **STL Containers** – Vectors and algorithms for entity organization  
- **Terminal UI** – For simulation display and player input  

## Core Concepts Implemented

- **Inheritance & Polymorphism:** Reusable logic between items, cities, and caravans.  
- **Autonomous behavior:** Non-player caravans operate automatically based on proximity and environment.  
- **Event-driven updates:** Storms, combat, and item discovery handled per simulation step.  
- **Smart memory management:** Implemented with **smart pointers (unique/shared)** to prevent leaks.  
- **Encapsulated world state:** All game logic managed through the Interface and Desert classes.  

## Gameplay Elements

### Cities
Act as trading hubs where caravans can **buy and sell goods**, **hire new crew** and **refill resources**.

### Caravans
Four main caravan types exist, each with distinct stats and purposes:
- **Commerce Caravan** – Focused on trade and cargo capacity.  
- **Military Caravan** – Strong attack and defense, ideal for combat.  
- **Barbarian Caravan** – Autonomous, aggressive NPC caravan.  
- **Hestia** – Special, resilient unit, ideal to survive.

### Items
Randomly generated items appear across the desert:
- **Treasure Chest** – Grants resources or wealth.  
- **Mine** – Damages caravans.  
- **Cage** – Traps a caravan temporarily.  
- **Pandora’s Box** – Random beneficial or harmful effect.  
- **Oasis** – Fully refills a caravan’s water supply.

## Combat System

When caravans occupy the same coordinates, a **battle** occurs:
- Only **user caravans** and **barbarians** engage in combat.  
- Barbarians do not consume water and never retreat.  
- Commerce and military caravans differ in attack strength and resilience.  

Water transfer does not occur during combat, maintaining fairness and resource balance.

## Commands

### In the simulation console
- **config \<file\>** – Load a map configuration file  
- **compraC \<city\> \<type\>** – Buy a caravan (`C` = Trade, `M` = Military, `S` = Secret)  
- **move \<id\> \<direction\>** – Move a caravan (`D` = Right, `E` = Left, `C` = Up, `B` = Down)  
- **tripul \<id\> \<n\>** – Hire `n` new crew members  
- **vende \<id\>** – Sell all goods from a caravan  
- **auto \<id\>** – Enable autonomous mode for a caravan  
- **stop \<id\>** – Disable autonomous mode for a caravan  
- **barbaro \<l\> \<c\>** – Spawn a barbarian caravan at the given coordinates  
- **areia \<l\> \<c\> \<r\>** – Trigger a sandstorm centered at (`l`, `c`) with radius `r`  
- **prox \<n\>** – Advance the simulation by `n` turns  
- **terminar** – End the simulation

## How to Build and Run


This project was developed using **CLion** (by JetBrains) as the main IDE.  
To run it, simply **open or import the project folder** in CLion, the IDE will automatically detect the configuration (CMakeLists.txt).  


---
*This work was completed as part of the “Object-Oriented Programming" course during the 2024/2025 academic year.*

