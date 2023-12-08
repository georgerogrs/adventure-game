New features Added to Game:

- Must specify which object you want to kill enemy with:
    - If you select the wrong object to kill the enemy, it will attack you
    - command "kill (enemy) with (object)" can be used
- If a player tries to take an item they are attacked by the enemy in the room
    - A player must kill all enemies in room in order to take an item
- Player can drop items using command "drop"
    - Player has a maximum inventory of 3 so may be necessary to drop some items
- Player has 3 lives
    - Instead of killing the player, an enemy now removes one life
    - If a player loses all lives they will die
    - User can type show lives to show their hearts
- If a player enters a room with no exits -> Game Over
- Main menu where a user can select level to be loaded into
    - To have a map added to the main menu -> Drop json file into project's
    resources folder
- Player can type hint for a list of all potential usable commands
    - "hint exits" also displays the possible exit names to the user
    - "hint tasks" also displays all remaining tasks for the player


Game fonts:
- Small Slant: https://patorjk.com/software/taag/#p=display&f=Small%20Slant&t=Adventure%20Quest
- Ghost: https://patorjk.com/software/taag/#p=display&f=Ghost&t=You%20win!
- Lil Devil: https://patorjk.com/software/taag/#p=display&f=Lil%20Devil&t=Game%20Over